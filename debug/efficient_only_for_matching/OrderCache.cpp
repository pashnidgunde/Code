#include "OrderCache.h"
#include <algorithm>

// add order to the cache
void OrderCache::addOrder(Order order)
{
    m_all_orders.emplace_back(order);
    auto index = m_all_orders.size() - 1;
    auto &new_order = m_all_orders.back();

    // indexes 
    auto &buy_or_sell_orders = (order.side()[0] == 'B') ? m_buy_orders : m_sell_orders;
    buy_or_sell_orders[new_order.securityId()] = index;
    m_orders_by_user[new_order.user()].insert(index);
    m_orders_by_company[new_order.company()].insert(index);
    m_orders_by_security_id[new_order.securityId()].insert(index);

    recalculate_matching_qty(order, true);
}

// remove order with this unique order id from the cache
void OrderCache::cancelOrder(const std::string& orderId)
{
    auto soft_delete = [&] (OrdersByIdMap& orders, const std::string& orderId)
    {
        auto it = orders.find(orderId); 
        if ( it != orders.end())
        {
            Order & order_details = m_all_orders[it->second];
            m_orders_by_user[order_details.user()].erase(it->second);
            m_orders_by_company[order_details.company()].erase(it->second);
            m_orders_by_security_id[order_details.company()].erase(it->second);
            orders.erase(orderId);

            recalculate_matching_qty(order_details, false);

            return true;
        }
        return false;
    };

    if (!soft_delete(m_buy_orders,orderId))
    {
        soft_delete(m_sell_orders,orderId);
    }
}

// remove all orders in the cache for this user
void OrderCache::cancelOrdersForUser(const std::string& user)
{
    auto soft_delete = [&] (const int order_index)
    {
        Order & order_details = m_all_orders[order_index];
        m_buy_orders.erase(order_details.orderId());
        m_sell_orders.erase(order_details.orderId());
        m_orders_by_company[order_details.company()].erase(order_index);
        m_orders_by_security_id[order_details.company()].erase(order_index);

        recalculate_matching_qty(order_details, false);

    };

    auto & order_indexes =  m_orders_by_user[user];
    for (const auto order_index : order_indexes)
    {
        soft_delete(order_index);
    }
    order_indexes.clear();
}

// remove all orders in the cache for this security with qty >= minQty
void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
    auto soft_delete = [&] (const int order_index)
    {
        Order & order_details = m_all_orders[order_index];
        m_buy_orders.erase(order_details.orderId());
        m_sell_orders.erase(order_details.orderId());
        m_orders_by_user[order_details.user()].erase(order_index);
        m_orders_by_company[order_details.company()].erase(order_index);

        recalculate_matching_qty(order_details, false);
    };

    // TO DO
    // replace below with equivalent of std::experiement::erase_if(...);

    auto& order_indexes = m_orders_by_security_id[securityId];
    for(auto it = order_indexes.begin(); it != order_indexes.end();)
    {
        Order & order_details = m_all_orders[*it];
        if(order_details.qty() >= minQty)
        {
            // replacing iterator with result of erase()
            // keeps the iterator valid
            soft_delete(*it);
            it = order_indexes.erase(it);
            recalculate_matching_qty(order_details, false);
        }
        else
        {
            it++;
        }
    }
}

// return the total qty that can match for the security id
unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
    Qty matching_qty = calculate_matching_qty_for_security(securityId);
    if (matching_qty > 0)
    {
        adjust_matching_qty_for_orders(securityId,matching_qty);
    }

    return matching_qty;
}

// Monish mentioned only open orders 
// return all open orders in cache in a vector
std::vector<Order> OrderCache::getAllOrders() const
{
    std::vector<Order> result;
    for (const auto& order : m_buy_orders)
    {
        result.emplace_back(m_all_orders[order.second]);
    }

    for (const auto& order : m_sell_orders)
    {
        result.emplace_back(m_all_orders[order.second]);
    }

    return result;
}

void OrderCache::recalculate_matching_qty(const Order& order_details, bool is_new)
{
    auto& company_to_qty_pair = m_security_id_to_company_qty[order_details.securityId()];
    auto &qty = (order_details.side()[0] == 'B') ?
                company_to_qty_pair[order_details.company()].first :
                company_to_qty_pair[order_details.company()].second;
    
    if (is_new)
        qty += order_details.qty();
    else
        qty -= order_details.qty();
}

OrderCache::Qty OrderCache::calculate_matching_qty_for_security(const SecurityId& security_id)
{
    Qty total_matching_qty = 0;
    BuyQty total_open_buy_qty = 0;
    SellQty total_open_sell_qty = 0;

    Qty buy_matching_qty = 0;
    Qty sell_matching_qty = 0;
    Qty matching_qty = 0;

    auto& compaines_to_qty = m_security_id_to_company_qty[security_id];
    auto buy_it = compaines_to_qty.begin();
    auto sell_it = compaines_to_qty.begin();
    for (auto& company_to_qty : compaines_to_qty)
    {
        // second is pair of buy qty and sell qty
        BuySellQtyPair& buy_sell_qty = company_to_qty.second;

        
        BuyQty& current_company_buy_qty = buy_sell_qty.first;
        SellQty& current_company_sell_qty = buy_sell_qty.second;

        buy_matching_qty = std::min(current_company_buy_qty, total_open_sell_qty);
        sell_matching_qty = std::min(current_company_sell_qty, total_open_buy_qty);
        
        matching_qty =  buy_matching_qty + sell_matching_qty;
        total_matching_qty += matching_qty;
        
        total_open_buy_qty = total_open_buy_qty + current_company_buy_qty - matching_qty;
        total_open_sell_qty = total_open_sell_qty + current_company_sell_qty - matching_qty;

       // adjust quantities to current buy and known previous sell
        current_company_buy_qty -= buy_matching_qty;
        sell_it->second.second -= buy_matching_qty;
        
        // adjust quantities to current sell and known previous buy
        current_company_sell_qty -= sell_matching_qty;
        buy_it->second.first -= buy_matching_qty;
        
        
    }

    return matching_qty;
}

void OrderCache::adjust_matching_qty_for_orders(const SecurityId& security_id, Qty matching_qty)
{
    // TO DO


}
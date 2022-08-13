#include "OrderCache.h"
#include <algorithm>
#include <iostream>

// add order to the cache
void OrderCache::addOrder(Order order)
{
    m_all_orders.emplace_back(order);
    auto index = m_all_orders.size() - 1;
    auto &new_order = m_all_orders.back();

    // record indexes 
    m_orders_by_order_id[new_order.orderId()] = index;

    m_orders_by_user[new_order.user()].insert(index);

    auto &buy_or_sell_orders = (order.side()[0] == 'B') ?
        m_orders_by_security_id[new_order.securityId()].first :
        m_orders_by_security_id[new_order.securityId()].second;
}

// remove order with this unique order id from the cache
void OrderCache::cancelOrder(const std::string& orderId)
{
    Index order_index = m_orders_by_order_id[orderId];
    auto& order = m_all_orders[order_index];
    
    // remove indexes
    m_orders_by_order_id.erase(orderId);

    m_orders_by_user[order.user()].erase(order_index);

    m_orders_by_security_id[order.securityId()].first.erase(order_index);
    m_orders_by_security_id[order.securityId()].second.erase(order_index);
}

// remove all orders in the cache for this user
void OrderCache::cancelOrdersForUser(const std::string& user)
{
    auto & order_indexes =  m_orders_by_user[user];
    for (const auto order_index : order_indexes)
    {
        Order & order = m_all_orders[order_index];
        m_orders_by_order_id.erase(order.orderId());
        m_orders_by_security_id[order.securityId()].first.erase(order_index);
        m_orders_by_security_id[order.securityId()].first.erase(order_index);
    }
    order_indexes.clear();
}

// remove all orders in the cache for this security with qty >= minQty
void OrderCache::cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
{
    auto soft_delete = [&] (OrderIndexes& indexes)
    {
        for(auto it = indexes.begin(); it != indexes.end();)
        {
            Order & order = m_all_orders[*it];
            
            if(order.qty() >= minQty)
            {
                m_orders_by_order_id.erase(order.orderId());
                m_orders_by_user[order.user()].erase(*it);
                it = indexes.erase(it);
            }
            else
            {
                it++;
            }
        }
    };

    soft_delete(m_orders_by_security_id[securityId].first);
    soft_delete(m_orders_by_security_id[securityId].second);
}

// return the total qty that can match for the security id
unsigned int OrderCache::getMatchingSizeForSecurity(const std::string& securityId)
{
    Qty total_match_qty = 0;
    Qty matching_qty = 0;

    auto can_match = [&](const auto& buy, const auto& sell)  { 
        std::cout << buy.company () << " : " << sell.company() << std::endl;
        return buy.company() != sell.company(); 
    };

    auto& buy_order_indexes = m_orders_by_security_id[securityId].first;
    auto& sell_order_indexes = m_orders_by_security_id[securityId].second;

    for (const auto& buy_order_index : buy_order_indexes)
    {
        auto& buy_order = m_all_orders[buy_order_index];
        std::cout << "Buy order id : " << buy_order.orderId() << std::endl;
        for (const auto& sell_order_index : sell_order_indexes)
        {
            auto& sell_order = m_all_orders[sell_order_index];
            if (sell_order.fully_matched()) continue;

            std::cout << "Sell order id : " << sell_order.orderId() << std::endl;
            
            matching_qty = std::min(buy_order.qty(), sell_order.qty());
            std::cout << "buy qty : " << buy_order.qty() << " , sell_order_qty : " <<  sell_order.qty() << std::endl;
            
            if (can_match(buy_order,sell_order) && matching_qty > 0)
            {
                std::cout << "matching _qty " << matching_qty << std::endl;

                total_match_qty+= matching_qty;
                
                std::cout << "total matching_qty " << total_match_qty << std::endl;
                buy_order.reduce_qty(matching_qty);
                sell_order.reduce_qty(matching_qty);

                if (buy_order.fully_matched()) break;
            }
        }
    }

    // erase orders with open qty = 0 
    auto soft_delete = [&] (OrderIndexes& indexes)
    {
        for(auto it = indexes.begin(); it != indexes.end();)
        {
            Order & order = m_all_orders[*it];
            if(order.qty() == 0)
            {
                m_orders_by_order_id.erase(order.orderId());
                m_orders_by_user[order.user()].erase(*it);
                it = indexes.erase(it);
            }
            else
            {
                it++;
            }
        }
    };

    soft_delete(m_orders_by_security_id[securityId].first);
    soft_delete(m_orders_by_security_id[securityId].second);
    return total_match_qty;
}

// Monish mentioned only open orders 
// return all open orders in cache in a vector
std::vector<Order> OrderCache::getAllOrders() const
{
    std::vector<Order> result;
    for (const auto& order : m_orders_by_order_id)
    {
        result.emplace_back(m_all_orders[order.second]);
    }

    return result;
}



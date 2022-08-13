#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string_view>  

class Order
{
  
 public:

  // do not alter signature of this constructor
 Order(const std::string& ordId, const std::string& secId, const std::string& side, const unsigned int qty, const std::string& user,
       const std::string& company)
   : m_orderId(ordId), m_securityId(secId), m_side(side), m_qty(qty), m_user(user), m_company(company) { }

  // do not alter these accessor methods 
  std::string orderId() const    { return m_orderId; }
  std::string securityId() const { return m_securityId; }
  std::string side() const       { return m_side; }
  std::string user() const       { return m_user; }
  std::string company() const    { return m_company; }
  unsigned int qty() const       { return m_qty; }
    
 private:
  
  // use the below to hold the order data
  // do not remove the these member variables  
  std::string m_orderId;     // unique order id
  std::string m_securityId;  // security identifier
  std::string m_side;        // side of the order, eg Buy or Sell
  unsigned int m_qty;        // qty for this order
  std::string m_user;        // user name who owns this order
  std::string m_company;     // company for user


// Introduced by Prashant
public:
    void reduce_qty(unsigned int match_qty)
    {
        m_qty -= match_qty;
    }

    bool fully_matched() { return m_qty == 0; }
};



// Provide an implementation for the OrderCacheInterface interface class.
// Your implementation class should hold all relevant data structures you think
// are needed. 
class OrderCacheInterface
{
   
public:
  
  // implememnt the 6 methods below, do not alter signatures

  // add order to the cache
  virtual void addOrder(Order order) = 0; 

  // remove order with this unique order id from the cache
  virtual void cancelOrder(const std::string& orderId) = 0; 

  // remove all orders in the cache for this user
  virtual void cancelOrdersForUser(const std::string& user) = 0; 

  // remove all orders in the cache for this security with qty >= minQty
  virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty) = 0; 

  // return the total qty that can match for the security id
  virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId) = 0; 

  // return all orders in cache in a vector
  virtual std::vector<Order> getAllOrders() const = 0;  

};

class OrderCache : public OrderCacheInterface
{
    public:
        OrderCache() = default;

        // Reserve with initial capacity to avoid unnecessary resizes
        OrderCache(size_t starting_capacity) : 
            m_initial_capacity(starting_capacity)
        {
            m_all_orders.reserve(starting_capacity);
        }

        // add order to the cache
        virtual void addOrder(Order order)
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

            buy_or_sell_orders.insert(index);
        }

        // remove order with this unique order id from the cache
        void cancelOrder(const std::string& orderId)
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
        void cancelOrdersForUser(const std::string& user)
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
        void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty)
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
        unsigned int getMatchingSizeForSecurity(const std::string& securityId)
        {
            Qty total_match_qty = 0;
            Qty matching_qty = 0;

            auto can_match = [&](const auto& buy, const auto& sell)  { 
                return buy.company() != sell.company(); 
            };

            auto& buy_order_indexes = m_orders_by_security_id[securityId].first;
            auto& sell_order_indexes = m_orders_by_security_id[securityId].second;

            for (const auto& buy_order_index : buy_order_indexes)
            {
                auto& buy_order = m_all_orders[buy_order_index];
                for (const auto& sell_order_index : sell_order_indexes)
                {
                    auto& sell_order = m_all_orders[sell_order_index];

                    // short circuit
                    if (sell_order.fully_matched()) continue;
    
                    matching_qty = std::min(buy_order.qty(), sell_order.qty());
                    
                    if (can_match(buy_order,sell_order) && matching_qty > 0)
                    {
                        total_match_qty+= matching_qty;
                        
                        buy_order.reduce_qty(matching_qty);
                        sell_order.reduce_qty(matching_qty);

                        // short circuit
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
        std::vector<Order> getAllOrders() const
        {
            std::vector<Order> result;
            for (const auto& order : m_orders_by_order_id)
            {
                result.emplace_back(m_all_orders[order.second]);
            }

            return result;
        }

    private:
        // string_view as key not tested on all platforms
        // Works on 64 bit RH7, not on win32 , apply as per platform
        #ifdef _STRING_VIEW_SUPPORTED
            using OrderId = std::string_view;
            using User = std::string_view;
            using Company = std::string_view;
            using SecurityId = std::string_view;
        #else
            using OrderId = std::string;
            using User = std::string;
            using Company = std::string;
            using SecurityId = std::string;
        #endif
        
        using Qty = unsigned int;
        using BuyQty = Qty;
        using SellQty = Qty;

        using Orders = std::vector<Order>;
        using OrdersIter = Orders::iterator;
        using Index = unsigned int; 

        using OrderIndexes = std::unordered_set<Index>;
        using BuyOrderIndexes = OrderIndexes;
        using SellOrderIndexes = OrderIndexes;
        using BuySellOrderIndexes = std::pair<BuyOrderIndexes,SellOrderIndexes>;

        // order by order id map
        using OrderIndexesByOrderId = std::unordered_map<OrderId,Index>;
        
        // orders by user
        using OrderIndexesByUser = std::unordered_map<User,OrderIndexes>;

        // buy and sell orders by securityid        
        using OrderIndexesBySecurityId = std::unordered_map<SecurityId,BuySellOrderIndexes>;

        // default  of OrderBook
        size_t m_initial_capacity = 0;
        Orders m_all_orders;
        OrderIndexesByOrderId m_orders_by_order_id;
        OrderIndexesByUser m_orders_by_user;
        OrderIndexesBySecurityId m_orders_by_security_id;

        // API's for testing only
    public:
        int capacity() { return m_initial_capacity; }
        int orderCount() { return m_all_orders.size();}
        int openOrderCount() { return getAllOrders().size(); }
        const Order& getOrderByOrderId(const OrderId& order_id) const
        {
            return m_all_orders[m_orders_by_order_id.at(order_id)];
        }
        const OrderIndexes& getOrdersByUser(const User& user_id) const
        {
            return m_orders_by_user.at(user_id);
        }
        const BuySellOrderIndexes& getOrdersBySecurityId(const SecurityId& security_id) const
        {
            return m_orders_by_security_id.at(security_id);
        }
        
        bool isOrderOpen(const OrderId& order_id) const {
            return (m_orders_by_order_id.find(order_id) != m_orders_by_order_id.end());
        }

};


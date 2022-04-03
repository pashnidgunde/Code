#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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
        OrderCache()
        {
            m_all_orders.reserve(CacheSize);
        }

        // add order to the cache
        virtual void addOrder(Order order); 

        // remove order with this unique order id from the cache
        virtual void cancelOrder(const std::string& orderId); 

        // remove all orders in the cache for this user
        virtual void cancelOrdersForUser(const std::string& user); 

        // remove all orders in the cache for this security with qty >= minQty
        virtual void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty); 

        // return the total qty that can match for the security id
        virtual unsigned int getMatchingSizeForSecurity(const std::string& securityId); 

        // return all orders in cache in a vector
        virtual std::vector<Order> getAllOrders() const;

    private:
        using OrderId = std::string_view;
        using User = std::string_view;
        using Company = std::string_view;
        using SecurityId = std::string_view;
        using Qty = unsigned int;
        using BuyQty = Qty;
        using SellQty = Qty;

        using Orders = std::vector<Order>;
        using OrdersIter = Orders::iterator;
        using Index = unsigned int; 
        using OrdersByIdMap = std::unordered_map<OrderId,Index>;
        using OrderIndexSet = std::unordered_set<Index>;
        using OrdersByUserMap = std::unordered_map<User,OrderIndexSet>;
        using OrdersByCompanyMap = std::unordered_map<Company,OrderIndexSet>;
        using OrdersBySecurityIdMap = std::unordered_map<SecurityId,OrderIndexSet>;
        using BuySellQtyPair = std::pair<BuyQty,SellQty>;
        using CompanyToBuySellQtyMap = std::unordered_map<Company,BuySellQtyPair>;
        using SecurityIdToCompanyQty = std::unordered_map<SecurityId, CompanyToBuySellQtyMap>;

        static const int CacheSize = 100;

        Orders m_all_orders;
        OrdersByIdMap m_buy_orders;
        OrdersByIdMap m_sell_orders;
        OrdersByUserMap m_orders_by_user;
        OrdersByCompanyMap m_orders_by_company;
        OrdersBySecurityIdMap m_orders_by_security_id;
        SecurityIdToCompanyQty m_security_id_to_company_qty;
    
    private:
        void recalculate_matching_qty(const Order& order, bool is_new);
        void adjust_total_qty_for_companies(const SecurityId& security_id, Qty matching_qty);
        Qty calculate_matching_qty_for_security(const SecurityId& security_id);
        void adjust_matching_qty_for_orders(const SecurityId& security_id, Qty matching_qty);
        
};
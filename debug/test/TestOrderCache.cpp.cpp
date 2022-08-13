#include <cassert>
#include "OrderCache.h"

void test_empty_cache()
{
    OrderCache cache;
    assert(cache.capacity() == 0);
}

void test_cache_capacity()
{
    OrderCache cache(100);
    assert(cache.capacity() == 100);
}

void test_add_order()
{
    OrderCache cache(100);

    Order b1 = Order("BuyOrder1", "Symbol1", "Buy", 1000, "User1", "Company1"); 
    cache.addOrder(b1);
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrderByOrderId("BuyOrder1").orderId() == "BuyOrder1");
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);

    Order b2 = Order("BuyOrder2", "Symbol2", "Buy", 1000, "User1", "Company2"); 
    cache.addOrder(b2);
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 2);
    assert(cache.getOrderByOrderId("BuyOrder2").orderId() == "BuyOrder2");
    assert(cache.getOrdersByUser("User1").size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);
}

void test_cancel_orders()
{
    OrderCache cache(100);

    Order b1 = Order("BuyOrder1", "Symbol1", "Buy", 1000, "User1", "Company1"); 
    cache.addOrder(Order(b1));
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);


    Order b2 = Order("BuyOrder2", "Symbol2", "Buy", 1000, "User2", "Company2"); 
    cache.addOrder(Order(b2));
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 2);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);
    
    cache.cancelOrder("BuyOrder1");
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);


    Order s1 = Order("SellOrder1", "Symbol1", "Sell", 1000, "User1", "Company1"); 
    cache.addOrder(Order(s1));
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 2);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 1);

    cache.cancelOrder("SellOrder1");
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
}


void test_cancel_orders_with_min_qty()
{
    OrderCache cache(100);

    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 100, "User1", "Company1"));
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrderByOrderId("BuyOrder1").orderId() == "BuyOrder1");
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);

    cache.addOrder(Order("BuyOrder2", "Symbol2", "Buy", 200, "User1", "Company2"));
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 2);
    assert(cache.getOrderByOrderId("BuyOrder2").orderId() == "BuyOrder2");
    assert(cache.getOrdersByUser("User1").size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);

    cache.addOrder(Order("Sell1", "Symbol1", "Sell", 400, "User2", "Company1"));
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 3);
    assert(cache.getOrderByOrderId("Sell1").orderId() == "Sell1");
    assert(cache.getOrdersByUser("User1").size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 1);

    cache.addOrder(Order("BuyOrder3", "Symbol2", "Buy", 800, "User2", "Company2"));
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getOrderByOrderId("BuyOrder3").orderId() == "BuyOrder3");
    assert(cache.getOrdersByUser("User2").size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);

    cache.addOrder(Order("Sell2", "Symbol2", "Sell", 1000, "User2", "Company2"));
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 5);
    assert(cache.getOrderByOrderId("Sell2").orderId() == "Sell2");
    assert(cache.getOrdersByUser("User2").size() == 3);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 1);

    // No matching qty < minQty
    cache.cancelOrdersForSecIdWithMinimumQty("Symbol1",500);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 1);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 5);
    
    cache.cancelOrdersForSecIdWithMinimumQty("Symbol1",150);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 4);

    cache.cancelOrdersForSecIdWithMinimumQty("Symbol1",50);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 3);

    // no cancel match
    cache.cancelOrdersForSecIdWithMinimumQty("Symbol2",1001);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 3);
    assert(cache.getOrdersByUser("User2").size() == 2);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 1);
    
    cache.cancelOrdersForSecIdWithMinimumQty("Symbol2",500);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);

    cache.cancelOrdersForSecIdWithMinimumQty("Symbol2",0);
    assert(cache.orderCount() == 5);
    assert(cache.openOrderCount() == 0);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol2").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol2").second.size() == 0);
}

void test_matching_logic_all_buy_no_matches()
{
    OrderCache cache(100);
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 100, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder3", "Symbol1", "Buy", 100, "User2", "Company2"));
    cache.addOrder(Order("BuyOrder4", "Symbol1", "Buy", 100, "User3", "Company3"));
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 0);
}

void test_matching_logic_all_sell_no_matches()
{
    OrderCache cache(100);
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User1", "Company1"));
    cache.addOrder(Order("SellOrder2", "Symbol1", "Sell", 100, "User1", "Company1"));
    cache.addOrder(Order("SellOrder3", "Symbol1", "Sell", 100, "User2", "Company2"));
    cache.addOrder(Order("SellOrder4", "Symbol1", "Sell", 100, "User3", "Company3"));
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 0);
}
    
void test_matching_logic_one_sell_multi_buy_diff_company()
{
    OrderCache cache(100);
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 200, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 100, "User2", "Company2"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User3", "Company3"));
    
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 3);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 1);
    assert(cache.getAllOrders().size() == 3);

    // Full match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 200);

    // Post match
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 0);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User3").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.getAllOrders().size() == 0);
}

void test_matching_logic_one_sell_multi_buy_diff_company_partial_match()
{
    OrderCache cache(100);
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 100, "User1", "Company2"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User1", "Company3"));
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 3);

    // partial match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 100);

    // Post match
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.getAllOrders().size() == 1);
}

void test_matching_logic_one_buy_multi_sell()
{
    OrderCache cache(100);
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 200, "User1", "Company1"));
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User2", "Company2"));
    cache.addOrder(Order("SellOrder2", "Symbol1", "Sell", 100, "User3", "Company3"));
    
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 3);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 2);
    assert(cache.getAllOrders().size() == 3);

    // Full match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 200);

    // Post match
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 0);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User3").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.getAllOrders().size() == 0);
}

void test_matching_logic_multi_buy_multi_sell_full_match()
{
    OrderCache cache(100);
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 100, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User2", "Company2"));
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User3", "Company2"));
    cache.addOrder(Order("SellOrder2", "Symbol1", "Sell", 100, "User4", "Company3"));
    
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 2);
    assert(cache.getAllOrders().size() == 4);

    // Full match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 200);

    // Post match
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 0);
    assert(cache.getOrdersByUser("User1").size() == 0);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User3").size() == 0);
    assert(cache.getOrdersByUser("User4").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.getAllOrders().size() == 0);
}

void test_matching_logic_multi_buy_multi_sell_partial_match()
{
    OrderCache cache(100);
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 300, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User2", "Company2"));
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User3", "Company2"));
    cache.addOrder(Order("SellOrder2", "Symbol1", "Sell", 200, "User4", "Company3"));
    
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 2);
    assert(cache.getAllOrders().size() == 4);

    // Full match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 300);

    // Post match
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 1);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 0);
    assert(cache.getOrdersByUser("User3").size() == 0);
    assert(cache.getOrdersByUser("User4").size() == 0);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 0);
    assert(cache.getAllOrders().size() == 1);
    
    // // validate qty
    assert(cache.getOrderByOrderId("BuyOrder1").qty() == 100);
}


void test_matching_logic_buy_sell_same_company_no_matches()
{
    OrderCache cache(100);
    cache.addOrder(Order("BuyOrder1", "Symbol1", "Buy", 300, "User1", "Company1"));
    cache.addOrder(Order("BuyOrder2", "Symbol1", "Buy", 100, "User2", "Company1"));
    cache.addOrder(Order("SellOrder1", "Symbol1", "Sell", 100, "User3", "Company1"));
    cache.addOrder(Order("SellOrder2", "Symbol1", "Sell", 200, "User4", "Company1"));
    
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 2);
    assert(cache.getAllOrders().size() == 4);

    // Full match
    assert(cache.getMatchingSizeForSecurity("Symbol1") == 0);

    // Post match
    assert(cache.orderCount() == 4);
    assert(cache.openOrderCount() == 4);
    assert(cache.getOrdersByUser("User1").size() == 1);
    assert(cache.getOrdersByUser("User2").size() == 1);
    assert(cache.getOrdersByUser("User3").size() == 1);
    assert(cache.getOrdersByUser("User4").size() == 1);
    assert(cache.getOrdersBySecurityId("Symbol1").first.size() == 2);
    assert(cache.getOrdersBySecurityId("Symbol1").second.size() == 2);
    assert(cache.getAllOrders().size() == 4);
    
    // // validate qty
    assert(cache.getOrderByOrderId("BuyOrder1").qty() == 300);
    assert(cache.getOrderByOrderId("BuyOrder2").qty() == 100);
    assert(cache.getOrderByOrderId("SellOrder1").qty() == 100);
    assert(cache.getOrderByOrderId("SellOrder2").qty() == 200);
}

void test_case_from_examples_1()
{
    // OrdId1 SecId1 Buy  1000 User1 CompanyA
    // OrdId2 SecId2 Sell 3000 User2 CompanyB
    // OrdId3 SecId1 Sell  500 User3 CompanyA
    // OrdId4 SecId2 Buy   600 User4 CompanyC
    // OrdId5 SecId2 Buy   100 User5 CompanyB
    // OrdId6 SecId3 Buy  1000 User6 CompanyD
    // OrdId7 SecId2 Buy  2000 User7 CompanyE
    // OrdId8 SecId2 Sell 5000 User8 CompanyE    

    OrderCache cache(100);
    cache.addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
    cache.addOrder(Order("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"));
    cache.addOrder(Order("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"));
    cache.addOrder(Order("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"));
    cache.addOrder(Order("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"));
    cache.addOrder(Order("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"));
    cache.addOrder(Order("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"));
    cache.addOrder(Order("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"));

    assert(cache.getMatchingSizeForSecurity("SecId1") == 0);
    assert(cache.getMatchingSizeForSecurity("SecId3") == 0);
    assert(cache.getMatchingSizeForSecurity("SecId2") == 2700);
}

void test_case_from_examples_2()
{
    // OrdId1 SecId1 Sell 100 User10 Company2
    // OrdId2 SecId3 Sell 200 User8 Company2
    // OrdId3 SecId1 Buy 300 User13 Company2
    // OrdId4 SecId2 Sell 400 User12 Company2
    // OrdId5 SecId3 Sell 500 User7 Company2
    // OrdId6 SecId3 Buy 600 User3 Company1
    // OrdId7 SecId1 Sell 700 User10 Company2
    // OrdId8 SecId1 Sell 800 User2 Company1
    // OrdId9 SecId2 Buy 900 User6 Company2
    // OrdId10 SecId2 Sell 1000 User5 Company1
    // OrdId11 SecId1 Sell 1100 User13 Company2
    // OrdId12 SecId2 Buy 1200 User9 Company2
    // OrdId13 SecId1 Sell 1300 User1 Company

    OrderCache cache(100);
    cache.addOrder(Order("OrdId1", "SecId1", "Sell", 100, "User10", "Company2"));
    cache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User8", "Company2"));
    cache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User13", "Company2"));
    cache.addOrder(Order("OrdId4", "SecId2", "Sell", 400, "User12", "Company2"));
    cache.addOrder(Order("OrdId5", "SecId3", "Sell", 500, "User7", "Company2"));
    cache.addOrder(Order("OrdId6", "SecId3", "Buy", 600, "User3", "Company1"));
    cache.addOrder(Order("OrdId7", "SecId1", "Sell", 700, "User10", "Company2"));
    cache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
    cache.addOrder(Order("OrdId9", "SecId2", "Buy", 900, "User6", "Company2"));
    cache.addOrder(Order("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"));
    cache.addOrder(Order("OrdId11", "SecId1", "Sell", 1100, "User13", "Company2"));
    cache.addOrder(Order("OrdId12", "SecId2", "Buy", 1200, "User9", "Company2"));
    cache.addOrder(Order("OrdId13", "SecId1", "Sell", 1300, "User1", "Company"));

    assert(cache.getMatchingSizeForSecurity("SecId1") == 300);
    assert(cache.getMatchingSizeForSecurity("SecId2") == 1000);
    assert(cache.getMatchingSizeForSecurity("SecId3") == 600);
}
void test_case_from_examples_3()
{
    // OrdId1 SecId3 Sell 100 User1 Company1
    // OrdId2 SecId3 Sell 200 User3 Company2
    // OrdId3 SecId1 Buy 300 User2 Company1
    // OrdId4 SecId3 Sell 400 User5 Company2
    // OrdId5 SecId2 Sell 500 User2 Company1
    // OrdId6 SecId2 Buy 600 User3 Company2
    // OrdId7 SecId2 Sell 700 User1 Company1
    // OrdId8 SecId1 Sell 800 User2 Company1
    // OrdId9 SecId1 Buy 900 User5 Company2
    // OrdId10 SecId1 Sell 1000 User1 Company1
    // OrdId11 SecId2 Sell 1100 User6 Company2

    OrderCache cache(100);
    cache.addOrder(Order("OrdId1", "SecId3", "Sell", 100, "User1", "Company1"));
    cache.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User3", "Company2"));
    cache.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User2", "Company1"));
    cache.addOrder(Order("OrdId4", "SecId3", "Sell", 400, "User5", "Company2"));
    cache.addOrder(Order("OrdId5", "SecId2", "Sell", 500, "User2", "Company1"));
    cache.addOrder(Order("OrdId6", "SecId2", "Buy", 600, "User3", "Company2"));
    cache.addOrder(Order("OrdId7", "SecId2", "Sell", 700, "User1", "Company1"));
    cache.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
    cache.addOrder(Order("OrdId9", "SecId1", "Buy", 900, "User5", "Company2"));
    cache.addOrder(Order("OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"));
    cache.addOrder(Order("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"));
    

    assert(cache.getMatchingSizeForSecurity("SecId1") == 900);
    assert(cache.getMatchingSizeForSecurity("SecId2") == 600);
    assert(cache.getMatchingSizeForSecurity("SecId3") == 0);
}


int main()
{
    test_empty_cache();
    test_cache_capacity();
    
    test_add_order();
    
    test_cancel_orders();
    
    test_cancel_orders_with_min_qty();

    test_matching_logic_all_buy_no_matches();
    test_matching_logic_all_sell_no_matches();
    test_matching_logic_one_sell_multi_buy_diff_company();
    test_matching_logic_one_buy_multi_sell();
    test_matching_logic_multi_buy_multi_sell_full_match();
    test_matching_logic_multi_buy_multi_sell_partial_match();
    test_matching_logic_buy_sell_same_company_no_matches();

    test_case_from_examples_1();
    test_case_from_examples_2();
    test_case_from_examples_3();

    return 0;
}

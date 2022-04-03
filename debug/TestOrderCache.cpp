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
    cache.addOrder(Order(b));
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);

    Order b2 = Order("BuyOrder2", "Symbol2", "Buy", 1000, "User2", "Company2"); 
    cache.addOrder(Order(b));
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 2);
}

void test_cancel_order()
{
    OrderCache cache(100);

    Order b1 = Order("BuyOrder1", "Symbol1", "Buy", 1000, "User1", "Company1"); 
    cache.addOrder(Order(b));
    assert(cache.orderCount() == 1);
    assert(cache.openOrderCount() == 1);

    Order b2 = Order("BuyOrder2", "Symbol2", "Buy", 1000, "User2", "Company2"); 
    cache.addOrder(Order(b));
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 2);

    cache.cancelOrder("BuyOrder1");
    assert(cache.orderCount() == 2);
    assert(cache.openOrderCount() == 1);

    Order b2 = Order("SellOrder1", "Symbol1", "Sell", 1000, "User", "Company1"); 
    cache.addOrder(Order(b));
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 2);

    cache.cancelOrder("SellOrder1");
    assert(cache.orderCount() == 3);
    assert(cache.openOrderCount() == 1);

}


int main()
{

    return 0;
}

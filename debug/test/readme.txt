Notes :

1. OrderCache.h implements the interface in same file for ease of header only testing
2. getAllOrders : returns only open orders and not all orders
3. string_views support is not tested, but is supported for RH7 64 bit , 32 bit windows isnt supported, worth a try
4. Refer to TestOrderCache.cpp for unit tests ( using asserts ), tests from examples in the end
5. Multithreaded version is not implemented

To compile for non windows :

g++ -Wall -Wextra --std=c++17 TestOrderCache.cpp -o TestOrderCache
./TestOrderCache


Thanks,
Prashant




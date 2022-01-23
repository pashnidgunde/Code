#include<iostream>
#include<bitset>
#include<cassert>

namespace pn
{
    namespace bs
    {
        void demo()
        {
            std::bitset<8> b1; // default all zeros
            std::cout << "b1 : " << b1 << std::endl;

            std::bitset<8> b2(255); // max that can fit into 8 bits [1....1]
            std::cout << "b2 : " << b2 << std::endl;

            std::bitset<8> b3(256); // doesn't fit into 8 bits [0....0]
            std::cout << "b3 : " << b3 << std::endl;

            //int num =20;
            //std::bitset<num> not_allowed; // expression must have constant value

            std::string bit_string = "110010";
            std::bitset<8> b4(bit_string); //[0,0,1,1,0,0,1,0]
            std::cout << "b4 : " << b4 << std::endl;
            std::bitset<8> b5(bit_string,2); // //[0,0,0,0,0,0,1,0]
            std::cout << "b5 : " << b5 << std::endl;
            std::bitset<8> b55(bit_string,2,3); // //[0,0,0,0,0,0,0,1]
            std::cout << "b55 : " << b55 << std::endl;

            std::bitset<8> b6("XXXXYYYY",1,'X','Y');
            std::cout << "b6 : " << b6 << std::endl; //[0,0,0,0,0,0,0,0]
            std::bitset<8> b61("XXXXYYYY",5,'X','Y');
            std::cout << "b61 : " << b61 << std::endl; //[0,0,0,{0,0,0,0,1}] // reads first 5 and substitutes right to left
            std::bitset<8> b62("XXXXYYYX",7,'Y','X');
            std::cout << "b62 : " << b62 << std::endl; //[0,{1,1,1,1,0,0,0}] // reads first 7 and substitutes right to left

            std::string alpha_bit_string = "aBaaBBaB";
            std::bitset<8> b7(alpha_bit_string,4,alpha_bit_string.size(),'a','B'); // [0,0,0,0,1,1,0,1] reads from position 0 to size
            std::cout << "b7 : " << b7 << std::endl;
        }
    }
}


namespace pn
{
    // namespace util
    // {
    //     template< typename E >
    //     using enable_enum_t = typename std::enable_if< std::is_enum<E>::value, 
    //                                             typename std::underlying_type<E>::type 
    //                                             >::type;

    //     }   // namespace details


    //     template< typename E >
    //     constexpr inline util::enable_enum_t<E> underlying_value( E e )noexcept
    //     {
    //         return static_cast< typename std::underlying_type<E>::type >( e );
    //     }   


    //     template< typename E , typename T>
    //     constexpr inline typename std::enable_if< std::is_enum<E>::value &&
    //                                         std::is_integral<T>::value, E
    //                                         >::type 
    //     to_enum( T value ) noexcept 
    //     {
    //     return static_cast<E>( value );
    //     }

    //     } // namespace utils

    // }

    namespace bs
    {
        std::bitset<4> buy_order(0b0001); 
        std::bitset<4> sell_order(0b0010); 
        std::bitset<4> in_the_market_mask(0b1111);
        std::bitset<4> out_of_market_mask(0b1011);
        std::bitset<4> sell_side_restricted(0b1100);

        std::bitset<4> cross_result = 0b0100;
        
        struct Order
        {
            std::bitset<4> order_flags; // ob0000
            void set_as_buy() { order_flags = pn::bs::buy_order; }
            void set_as_sell() { order_flags = pn::bs::sell_order; }
            void in_the_market() { order_flags[2] = 1; }
            void out_of_market() { order_flags[2] = 0; }
            void from_sell_side_member() { order_flags[3]=1;}
            void from_buy_side_member() { order_flags[4]=1;}
        };

        
        struct MatchManager
        {
            enum class ReasonNotToCross
            {
                SUCCESS = 4,
                SAME_BUY_SIDE = 1,
                SAME_SELL_SIDE = 2,
                NOT_IN_MARKET = 0,
                SELL_SIDE_RESTRICTED = 12,
                BUY_SIDE_RESTRICTED = 16
            };

            bool can_cross(const Order& lhs, const Order& rhs)  
            {
                std::cout << "lhs order flags : " << lhs.order_flags
                    << " , rhs order flags : " << rhs.order_flags
                    << " , result : " << (lhs.order_flags & rhs.order_flags)
                    << std::endl;

                m_reason_not_to_cross = static_cast<ReasonNotToCross>((lhs.order_flags & rhs.order_flags).to_ulong());
                return (m_reason_not_to_cross == ReasonNotToCross::SUCCESS);
            }

            ReasonNotToCross m_reason_not_to_cross = ReasonNotToCross::SUCCESS;
        };

        void test()
        {
            MatchManager mm;
            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                sell_order.set_as_buy();
                assert(!mm.can_cross(buy_order,sell_order)); // can not cross, both buy
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::SAME_BUY_SIDE);
            }
            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_sell();
                sell_order.set_as_sell();
                assert(!mm.can_cross(buy_order,sell_order)); // can not cross, both sell    
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::SAME_SELL_SIDE);
            }
            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                sell_order.set_as_sell();
                assert(!mm.can_cross(buy_order,sell_order)); // can not cross, opposite but both not in market
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::NOT_IN_MARKET);
            }
            
            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                buy_order.in_the_market();
                sell_order.set_as_sell();
                assert(!mm.can_cross(buy_order,sell_order)); // can not cross, buy in market and sell not in market
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::NOT_IN_MARKET);
            }

            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                buy_order.in_the_market();
                sell_order.set_as_sell();
                sell_order.in_the_market();
                assert(mm.can_cross(buy_order,sell_order)); // must cross 
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::SUCCESS);   
            }
            
            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                buy_order.in_the_market();
                sell_order.set_as_sell();
                sell_order.in_the_market();
                assert(mm.can_cross(buy_order,sell_order)); // must cross
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::SUCCESS);   
            }

            {
                Order buy_order;
                Order sell_order;
                buy_order.set_as_buy();
                buy_order.in_the_market();
                sell_order.set_as_sell();
                sell_order.in_the_market();
                buy_order.from_sell_side_member();
                sell_order.from_sell_side_member();
                assert(!mm.can_cross(buy_order,sell_order)); // must not cross
                assert(mm.m_reason_not_to_cross == pn::bs::MatchManager::ReasonNotToCross::SELL_SIDE_RESTRICTED);
            }
        }
    }
}


int main()
{
    pn::bs::demo();
    pn::bs::test();
    return 0;
}


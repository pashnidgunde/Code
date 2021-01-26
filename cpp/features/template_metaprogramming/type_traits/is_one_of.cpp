#include <iostream>

template<typename T, T v>
struct integral_constant
{
    using type = T;
    static constexpr T value = v;
};

template <bool b> 
struct conditional : public integral_constant<bool,b>
{
};

using true_type = conditional<true>;
using false_type = conditional<false>;

template<typename T, typename... Types>
struct is_one_of;

template<typename T>
struct is_one_of<T> : false_type {};

template<typename T, typename ... P1ToN>
struct is_one_of<T,T,P1ToN...> : true_type {};

template<typename T, typename P0, typename ... P1ToN>
struct is_one_of<T,P0,P1ToN...> : is_one_of<T,P1ToN...> {};


int main()
{
    std::cout << is_one_of<int,float>::value;
    std::cout << is_one_of<int,int>::value;
                 // is_one_of<int,float,{}> : is_one_of<int,{float}
                 // 
                 is_one_of<float, int, double,char,float>;
    return 0;
}
// conditional
// takes 2 types and gives a type based on compile time first type
// possible implementation
// template <bool, typename T, typename F>
// struct conditional
// {
//     using type = T;
// }
// template <typename T, typname F>
// struct conditional<false,T,F>
// {
//      using type = F;    
// }       


#include <iostream>
#include <type_traits>
int main()
{
    using IntType = std::conditional<true,int,double>::type;
    using DoubleType = std::conditional<false,int,double>::type;
    using conditionalBoolType = std::conditional<sizeof(int) == sizeof(double), bool, bool>::type;

    static_assert(std::is_same<IntType, int>::value, "Must be of int type");
    static_assert(std::is_same<DoubleType, DoubleType>::value, "Must be of int type");
    static_assert(std::is_same<conditionalBoolType, bool>::value, "Must be of int type");
}
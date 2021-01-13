#include<iostream>
#include<type_traits>

namespace pn
{
class X
{

};
}

template<typename T>
void is_same_type()
{
    std::cout << std::is_same<std::decay_t<T>,pn::X>::value;
}

int main()
{
    //const X x;
    is_same_type<const pn::X&>();
    // is_same_type<X&>();
    // is_same_type<X>();
    // is_same_type<X*>();

    return 0;
}
#include <iostream>

// template alias 
// using after template
template<class ...>
using void_t = void;

template<class T, class = int>
struct X
{
    static constexpr int value = 1;
};

template<class T>
struct X <T, void_t<decltype(T::foobar())>>
{
    static constexpr int value = 2;
};

struct fb
{
    static constexpr void foobar();
};

int main()
{
    std::cout << X<int,void>::value << std::flush;
    std::cout << X<fb>::value << std::flush;  // X<fb, int> x
    std::cout << X<fb,void>::value << std::flush;

    return 0;
}
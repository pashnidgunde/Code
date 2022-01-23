#include <iostream>
#include <type_traits>

// template alias 
// using after template
template<class ...>
using void_t = void;

namespace pn
{
    namespace void_t_demo
    {
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
    }

    namespace void_t_demo1
    {
        struct Default
        {
            void foobar() { /* has foobar and is default constructible */ }
        };

        struct NonDefault
        {
            NonDefault() = delete;
            void foobar() { /* has foobar but is not default constructible */ }
        };

        template <typename T, typename Enable = void>
        struct has_foobar : public std::false_type {};

        // specialization
        // Would work only if object can be default constructible
        // declval solves the problem
        //template<typename T>
        //struct has_foobar<T,void_t<decltype(T::foobar())>> : public std::true_type {};

        // specialization with declval
        // in unevaluated context, declval<T> generate a r value reference so that 
        // member functions can be used
        template<typename T>
        struct has_foobar<T,void_t<decltype(std::declval<T>().foobar())>> : public std::true_type {};
    }
}


int main()
{
    // try matching all templates with given type reading from top to bottom
    std::cout << pn::void_t_demo::X<int,void>::value << std::flush;
    std::cout << pn::void_t_demo::X<pn::void_t_demo::fb>::value << std::flush;  // X<fb, int> x
    std::cout << pn::void_t_demo::X<pn::void_t_demo::fb,void>::value << std::flush;

    // 
    std::cout << pn::void_t_demo1::has_foobar<int>::value; // false type
    std::cout << pn::void_t_demo1::has_foobar<pn::void_t_demo::fb>::value; 
    std::cout << pn::void_t_demo1::has_foobar<pn::void_t_demo1::Default>::value; 
    std::cout << pn::void_t_demo1::has_foobar<pn::void_t_demo1::NonDefault>::value; 

    return 0;
}
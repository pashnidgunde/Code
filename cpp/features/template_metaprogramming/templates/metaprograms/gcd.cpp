#include <iostream>

// https://www.programiz.com/c-programming/examples/hcf-recursion

namespace pn
{
    namespace runtime
    {
        int gcd(int num1, int num2)
        {
            if (num2!=0)
            {
                return gcd(num2, num1%num2);
            }
            return num1;
        }
    }

    namespace compile_time
    {
        template<size_t Num1, size_t Num2>
        struct GCD
        {
            static constexpr size_t value = GCD<Num2,Num1%Num2>::value;
        };

        template <size_t Num1>
        struct GCD<Num1,0>
        {
            static_assert(Num1 != 0); // gcd(0,0) is undefiened, disallow
            static constexpr size_t value = Num1;
        };

    }

    // namespace variadic_gcd
    // {
    //     template<size_t ...nums>
    //     struct GCD
    //     {
    //         static constexpr size_t value = GCD<GCD<Num1,Num2>::value,rest...>::value;
    //     };

    //     template<size_t Num1, size_t Num2>
    //     struct GCD<Num1,Num2>
    //     {
    //         static constexpr size_t value = GCDImpl<Num2,Num1%Num2>::value;
    //     };

    //     template <size_t Num1>
    //     struct GCD<Num1,0>
    //     {
    //         static_assert(Num1 != 0); // gcd(0,0) is undefiened, disallow
    //         static constexpr size_t value = Num1;
    //     };

    // }


    namespace variadic_gcd
    {
        template<size_t ... Nums>
        struct GCD;

        template<size_t Num1, size_t Num2>
        struct GCD<Num1, Num2>
        {
            static constexpr size_t value = GCD<Num2,Num1%Num2>::value;
        };

        template <size_t Num1>
        struct GCD<Num1,0>
        {
            static_assert(Num1 != 0); // gcd(0,0) is undefiened, disallow
            static constexpr size_t value = Num1;
        };

        template<size_t Num1, size_t Num2, size_t ...Nums>
        struct GCD<Num1,Num2,Nums...> : public GCD<GCD<Num1,Num2>::value,Nums...>
        {
            //static constexpr size_t value =  GCD<GCD<Num1,Num2>::value,Nums...>::value;
        };

        // GCD<10,20,30> = GCD<GCD<10,20>::value,30>::value

        //GCD<10,20,30> = GCD<GCD<10,20>::value,30>::value

    }

}

int main()
{
    std::cout << pn::runtime::gcd(60,90) << std::endl;
    std::cout << pn::compile_time::GCD<60,90>::value << std::endl;
    std::cout << pn::variadic_gcd::GCD<10,20,30,40>::value << std::endl;
    std::cout << pn::variadic_gcd::GCD<3,5,2,6,8,6>::value << std::endl;
    //std::cout << pn::compile_time_enable_if::GCD<60,90>::value << std::endl;
    return 0;
}

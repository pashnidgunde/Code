#include <iostream>

long factorial(long number)
{
    if (number == 0) return 0;
    if (number == 1) return 1;
    return number * factorial(number - 1);
}

template<unsigned int number>
struct Factorial
{
    static constexpr long value = number * Factorial<number-1>::value;
};



template<>
struct Factorial<1>
{ 
    static constexpr long value = 1;
};

template<>
struct Factorial<0>
{ 
    static constexpr long value = 0;
}; 

int main()
{
    std::cout << factorial(0) << std::endl;
    std::cout << factorial(1) << std::endl;
    std::cout << factorial(2) << std::endl;
    std::cout << factorial(3) << std::endl;

    //std::cout << Factorial<0>::value << std::endl;
    std::cout << Factorial<1>::value << std::endl;
    std::cout << Factorial<2>::value << std::endl;
    std::cout << Factorial<3>::value << std::endl;

    return 0;
}

 
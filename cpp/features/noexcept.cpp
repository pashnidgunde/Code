#include<iostream>

// In general 
// noexcept specifier
// func() noexpcet ( const bool expression ) // where expression must be evaluated at compile time
// noexcept(const bool expression) // noexcept operator that evaluates to compile time true or false

void fun() noexcept(false); // function does not throw
void (*fp)(); // function pointer fp that points to may throw
void g(void () noexcept); // g takes a pointer to a function that will not throw

// can throw
// same as fun1() noexcept(false)
void fun1() {} 

// must not throw
// equal to noexcept(true) 
// if throws then abnormal termination, catch wont catch it
void fun2() noexcept {}

// same as void fun3() noexcept
// if throws then abnormal termination, catch wont catch it
void fun3() noexcept(true) {}

// same as void fun4()
// can throw and will be cought
void fun4() noexcept(false) {}

// function marked as noexcept but still throws
// outcome abnormal termination, but compiler warns 
void fun5() noexcept
{
    throw(1);
}

// noexcept(false) but calls noexcept(false)
// crash
void fun6()
{
    fun5(); 
}

// doesnt throw
// first noexecept is specifier
// second noexcept is operator
// sweet
void fun7() noexcept(noexcept(fun4()))
{
    throw 1;
}


int main()
{

    // note this is not call to fun1() but a call to noexcept operator 
    std::cout << "fun 1 throws ? " << noexcept(fun1()) << '\n'; 
    std::cout << "fun 2 throws ? " << noexcept(fun2()) << '\n';
    std::cout << "fun 3 throws ? " << noexcept(fun3()) << '\n';
    std::cout << "fun 4 throws ? " << noexcept(fun4()) << '\n';

    // note constexpr operator evaluates at compile time
    constexpr bool x = noexcept(fun1());

    // Will be caught, no abnormal termination
    try
    {
        fun7();
    }
    catch(...)
    {
        std::cerr << "caught fun7 exceptoin" << '\n';
    }
    
    // try to catch it but as its marked nothrow (true), 
    // it wil crash instead of being caught
    try
    {
        std::cout << "calling fun6" << '\n';
        fun6(); // is noexcept(false) but it calls fun5 which is noexcept(true)
    }
    catch(const std::exception& e)
    {
        std::cout << "will never be caught fun6" << '\n';
        std::cerr << e.what() << '\n';
    }

    // try to catch it but as its marked nothrow (true), 
    // it wil crash instead of being caught
    try
    {
        std::cout << "calling fun5" << '\n';
        fun5(); // abonormal termination no catch
    }
    catch(const std::exception& e)
    {
        std::cout << "will never be caught fun5" << '\n';
        std::cerr << e.what() << '\n';
    }
   
    return 0;
}
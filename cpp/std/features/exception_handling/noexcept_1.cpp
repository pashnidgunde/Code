#include <iostream>
#include <vector>
#include <cstdio>

struct S
{
    S() { puts("S");}
    S(int) { puts("S(int)");}
    S(const S&) { puts("S(const S&)");}
    S(S&&) { puts("S(&&)");}
    ~S() {puts ("~S()"); }

};

// Make sure to use noexcept to functions which dont throw.
struct NoExceptS
{
    NoExceptS() { puts("NoExceptS");}
    NoExceptS(int) { puts("NoExceptS(int)");}
    NoExceptS(const NoExceptS&) { puts("NoExceptS(const NoExceptS&)");}
    NoExceptS(NoExceptS&&) noexcept { puts("NoExceptS(&&)");}
    ~NoExceptS() {puts ("~NoExceptS()"); }
};

//auto main() -> decltype(int)
int main()
{
    // For each emplace 
    // vector capacity doubles if reached capacity and objects are moved to new location
    // invoking copy constructor and destrcutor
    {
    
    std::vector<S> vec;
    vec.emplace_back(3);
    std::cout << vec.capacity() << '\n';
    vec.emplace_back(3);
    std::cout << vec.capacity() << '\n';
    // vec.emplace_back(3);
    // std::cout << vec.capacity() << '\n';
    // vec.emplace_back(3);
    // std::cout << vec.capacity() << '\n';
    // vec.emplace_back(3);
    // std::cout << vec.capacity() << '\n';
    }

    std::cout << "======================================" << '\n';

    // With noexcept on move constructor , we told compiler that we can move NoExcept object with stong exception safe guarantee
    // With that, they can be moved instead of copy
    // This way compiler can be more efficient in generating code underneath
    {
        std::vector<NoExceptS> vec;
        vec.emplace_back(3);
        std::cout << vec.capacity() << '\n';
        vec.emplace_back(3);
        std::cout << vec.capacity() << '\n';
        // vec.emplace_back(3);
        // std::cout << vec.capacity() << '\n';
        // vec.emplace_back(3);
        // std::cout << vec.capacity() << '\n';
        // vec.emplace_back(3);
        // std::cout << vec.capacity() << '\n';
    }


    return 0;
}
#include <functional>
#include <iostream>

void print(int number) { std::cout << number << std::endl; }

struct Foo
{
    Foo(int number) : number_(number) {}
    int number_;
    void print() const
    {
        std::cout << number_ << std::endl;
    }

    void printx(int x) const
    {
        std::cout << number_ + x << std::endl;
    }
};

struct PrintPredicate
{
    PrintPredicate(int number) : number_(number) {}
    void operator()() { std::cout << number_ << std::endl;}
    int number_;
};


int main() { 

    // 1. free functions
    std::function<void(int)> printFunc = print;
    printFunc(10);

    // 2. lambda functions
    std::function<void()> printFunc1 =  [] () { print(100); };
    printFunc1();

    // std::bind
    std::function<void()> printWithBindFunc = std::bind(print,1000);
    printWithBindFunc();

    // Use of member function in std::function
    std::function<void(const Foo&)> fooMemberFunction = &Foo::print;
    const Foo foo(100);
    fooMemberFunction(foo);
    // implicit conversion to Foo
    fooMemberFunction(200);

    // Use of data member in std::function
    std::function<int(Foo const&)> fooMember = &Foo::number_;
    // implicit conversion to Foo
    std::cout << "Member of foo :: " << fooMember(foo);

    // store a call to member function and object
    using std::placeholders::_1;
    std::function<void(int)> fPlaceHolder = std::bind(&Foo::printx, foo, _1);
    fPlaceHolder(2);

    // store a call to member function and object pointer
    std::function<void(int)> fPlaceHolderObjectPointer = std::bind(&Foo::printx, &foo, _1);
    fPlaceHolderObjectPointer(5);

    std::function<void()> printPredicateFunc = PrintPredicate(500);
    printPredicateFunc(); 

    return 0;

}
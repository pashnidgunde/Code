// This is a demonstration that 
// 1. virtual functions with different signature don't inhabit virtual mechanism
// 2. Even if the derived is not declared virtual and has base function virtual, derived is virtual
// 3. in c++11 you can have override that signifies that you are overridding
// 4. The destructor of virtual base class should be virtual else memory leak
//     --> No need to make destructor virtual if new objects are not getting created using new

#include <iostream>

class Base
{
    public:
        virtual void print()
        {
            std::cout << "In Base::print" << std::endl;
        }

        //~Base() :: if not virtual this will be called directly
        virtual ~Base()  
        {
            std::cout << "In Base destructor" << std::endl;
        }
};

class Derived : public Base
{
    public:
        void print(int x)
        {
            std::cout << "In Derived::print(int)" << std::endl;
        }

        // Even this is not declared virtual this is treated as virtual
        void print() 
        //void print() override ( c++ 11 )
        {
            std::cout << "In derived print " << std::endl;
        }

        ~Derived()
        {
            std::cout << "In derived destructor" << std::endl;
        }
};


int main()
{
    Base *p = new Derived();
    //p->print(0); // compilation error because print in derived has different signature
    p->print(); // prints derived
    std::cout << "sizeof derived :: " << sizeof(Derived) << std::endl;
    std::cout << "sizeof derived :: " << sizeof(Base) << std::endl;
    delete p;
    return 0;
}

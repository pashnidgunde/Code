#include <iostream>

class X
{
    public:
        virtual void print() = 0;
};

void X::print()
{
}

int main()
{
    X *x = new X();
    return 0;
}

//Template that accepts auto

#include <iostream>

template < class T>
void fun(T a)
{
    std::cout << a << std::endl;
}


int main()
{
    auto t = 10.40;
    fun(t);
    return 0;
}

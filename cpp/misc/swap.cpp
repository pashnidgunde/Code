// Implement version of std::swap

#include <iostream>

// Note that the values are passed by ref.
template < class T>
void swap ( T& l, T& r)
{
    T x;
    x = l;
    l = r;
    r = x;
}



int main()
{
    int a = 10;
    int b = 20;


    int *p = &a;
    int *q = &b;

    swap( a, b);
    std::cout << a << " :: " << b << std::endl;
    // values are passed and not pointers
    swap( *p, *q);
    std::cout << a << " :: " << b << std::endl;

    // standard swap does not swap values in case of pointers
    std::swap(p,q);
    std::cout << a << " :: " << b << std::endl;
    return 0;
}

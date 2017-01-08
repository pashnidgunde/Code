#include <iostream>


int main()
{
    // compile time assert
    static_assert( sizeof(int) == 4 , "size of integer is not 4") ;

    return 0;
}

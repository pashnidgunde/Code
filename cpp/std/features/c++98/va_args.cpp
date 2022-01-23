#include <iostream>
#include <stdarg.h>

void print(size_t count, ...)
{
    va_list v1;
    va_start(v1,count);
    for (auto i=0;i<count;++i)
    {
        std::cout << va_arg(v1,int);
    }
    va_end(v1);
}

int main()
{
    print(5,1,2,3,4,5);
}

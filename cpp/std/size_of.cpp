#include <iostream>
#include <initializer_list>

template<typename ...T>
size_t size(T...args)
{
    (void)std::initializer_list<int>{(args,0)...};
    static_assert(sizeof...(args) == sizeof...(T), "Sizes must be same");
    return sizeof...(args); // or sizeof...(T);
}

int main()
{
    std::cout << size(1);
    std::cout << size(1,2);
    std::cout << size(1,2,3,4);
    return 0;
}
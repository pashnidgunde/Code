#include<iostream>

template<typename T>
struct rank
{
    static constexpr size_t value = 0;
};

template<typename T,size_t N>
struct rank<T[N]> {
    static constexpr size_t value = 1+ rank<T>::value;
};
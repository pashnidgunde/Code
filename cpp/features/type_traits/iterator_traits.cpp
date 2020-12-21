// Iterator Traits
// difference_type
// value_type

#include <type_traits>
#include <vector>
#include <iostream>

template<typename Iter>
void print(Iter begin, Iter end)
{
    typename std::iterator_traits<Iter>::difference_type count = std::distance(begin,end);
    while (count > 0)
    {
        typename std::__iterator_traits<Iter>::value_type value = *begin;
        std::cout << value;
        count --;
        begin++;
    }
}


int main()
{
    std::vector<int> v{1,2,3,4};
    print(v.begin(),v.end());
    return 0;
}

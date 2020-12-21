// https://en.cppreference.com/w/cpp/algorithm/iter_swap

// Possible implementation
//template<typename FwdIter>
//void iter_swap(FwdIter lhs, FwdIter rhs)
//{
//  std::swap(*lhs,*rhs);
//}

#include <iostream>
#include <vector>

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
    std::vector<int> v{1,2,3};
    std::cout <<"Before : " ;
    print(v.begin(),v.end());

    std::iter_swap(v.begin(),v.end()-1);
    
    std::cout <<"\n After : " ;
    print(v.begin(),v.end());

    return 0;
}

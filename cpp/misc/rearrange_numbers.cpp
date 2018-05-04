/* Arrange numbers is such a way that every second 
number  should be greater than its left number and right number */

// Solution 1 : Sort numbers and revisit numbers  -- > O(N log N)
// Solution 2 : Visit number once to determine swap --> O(N)

#include <vector>
#include <array>
#include "algo/sort/bubble_sort.h"
#include "functors.h"
#include "utils.h"

template<typename Iter>
void rearrange_naive(Iter begin , Iter end)
{
    // TODO : To use the best sorting algo
    // generic bubble sort is used for testing purpose only
    pn::algo::bubbleSort(begin,end,pn::functors::less<int>());
    while(begin+2 != end)
    {
        // TODO
        std::swap(*(begin+1), *(begin+2));
        std::advance(begin,2);
    }
}

template<typename Iter>
void rearrange_efficient(Iter begin, Iter end)
{
    while (true)
    {
        if (begin == end || begin+1 == end)
            break;
        
        if (*(begin) > *(begin+1))
        {
            std::swap(*begin, *(begin+1));
        }
    
        std::advance(begin,1);
        
        if (begin == end || begin+1 == end)
            break;

        std::swap(*(begin+1) , *(begin+2));
        std::advance(begin, 1);
    }
}


int main()
{
    std::vector<int> vec{1,5,6,9,2,3};
    std::vector<int> vec2(vec);
    rearrange_naive(std::begin(vec),std::end(vec));
    pn::utils::print<std::vector<int>::iterator> 
        (std::begin(vec),std::end(vec));

    rearrange_efficient(std::begin(vec2),std::end(vec2));
    pn::utils::print<std::vector<int>::iterator> 
        (std::begin(vec2),std::end(vec2));

    std::array<int, 10> random;
    for (int i=0;i<10;i++)
    {
        random[i] = rand() % 100;
    }

    rearrange_efficient(std::begin(random),std::end(random));
    pn::utils::print<std::array<int,10>::iterator> 
        (std::begin(random),std::end(random));

    return 0;
}

#include <iostream>
#include <vector>
//#include <algorithm>

namespace algorithm
{
    template <typename T>
    struct less
    {
        bool operator()(const T& lhs, const T& rhs) const
        {
            return lhs < rhs;
        }
    };

    template <typename T>
    struct greater
    {
        bool operator()(const T& lhs, const T& rhs) const
        {
            return lhs > rhs;
        }
    };
}

// The operator tells the what is to be compared.
// Operator less or greater
template<typename O>
void sort(std::vector<int>& numbers, O op )
{
    size_t size = numbers.size();
    for (size_t i = 0; i< size ; ++i)
    {
        for (size_t j = 0;j<size ; ++j)
        {
            if (op(numbers[i],numbers[j]))
            {
                std::swap(numbers[i],numbers[j]);
            }
        }
    }
}

int main()
{
    std::vector<int> v { 10,9,8,7,6,5,4,3,2,1};
    
    // Sort using standard comparator less
    //sort(v,std::less<int>());
    sort(v,algorithm::less<int>());
    for (const auto& e : v)
        std::cout << e << " " ;
    std::cout << std::endl;

    // Sort using standard comparator greater
    //sort(v,std::greater<int>()); 
    sort(v,algorithm::greater<int>());   
    for (const auto& e : v)
        std::cout << e << " " ;

    return 0;

}
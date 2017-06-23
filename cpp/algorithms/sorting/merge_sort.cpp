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




void print(const std::vector<int>& v)
{
    for (const auto& e : v)
        std::cout << e << " " ;
    std::cout << std::endl;
}

void merge(std::vector<int>&numbers, int l , int mid, int r  )
{
    
}

// The operator tells the what is to be compared.
// Operator less or greater
template<typename T>
void sort(std::vector<T>& numbers, int l , int r)
{
    if ( l == r ) return;
    //auto mid = (l+r) / 2
    // This is to avoid overflow
    auto mid = (l + (r-l) / 2);

    sort(numbers, l, mid);
    sort(numbers, mid+1, r);

    return merge(numbers, l, mid, r);
}

int main()
{
    std::vector<int> v {10,9,8};
    //std::vector<int> v { 10,9,8,7,6,5,4,3,2,1};

    // Sort using standard comparator less
    //sort(v,std::less<int>());
    sort(v, 0, v.size() -1 );
    print(x);
    

    // Sort using standard comparator greater
    //sort(v,std::greater<int>()); 
    //sort(v,algorithm::greater<int>());   
    //for (const auto& e : v)
    //    std::cout << e << " " ;

    return 0;

}
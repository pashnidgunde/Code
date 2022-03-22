//https://www.techiedelight.com/check-subarray-with-0-sum-exists-not/

#include <vector>
#include <cassert>
#include <unordered_set>

// O(n*n)
namespace crude
{
    bool subarray_with_sum_zero_exists_or_not(const std::vector<int>& v)
    {
        std::unordered_set<int> lookup { v.begin(), v.end() };
        for (auto i = v.begin(); i != v.end(); i++)
        {
            auto sum = *i;
            for(auto j = i+1; j != v.end(); j++ )
            {
                if ( sum + *j == 0) return true;
                sum = sum + *j;
            }
        }
        
        return false;
    }

}

// keep track of sum , if sum is seen before which means we have a sum with zero
bool subarray_with_sum_zero_exists_or_not(const std::vector<int>& v)
{
    std::unordered_set<int> store;
    store.insert(0);
    auto sum = 0;
    for (const auto& elem : v)
    {
        sum+= elem;
        if (store.find(sum) != store.end()) return true;
        store.insert(sum);
    }

    return false;
}


int main()
{
    std::vector<int> v { 0 };
    assert(subarray_with_sum_zero_exists_or_not(v) == true);

    std::vector<int> v1 { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
    assert(subarray_with_sum_zero_exists_or_not(v1) == true);

    std::vector<int> v2 { 1,2,3,-6 };
    assert(subarray_with_sum_zero_exists_or_not(v2) == true);

    std::vector<int> v3 { 1,2,3 };
    assert(subarray_with_sum_zero_exists_or_not(v3) == false);

    return 0;
}
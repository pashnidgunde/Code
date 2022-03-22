//https://www.techiedelight.com/check-subarray-with-0-sum-exists-not/

#include <vector>
#include <cassert>
#include <unordered_map>
#include <iostream>

// O(n*n)
namespace crude
{
    void print_subarray_with_sum(const std::vector<int>& v, int expected_sum)
    {
        for (auto i = v.begin(); i != v.end(); i++)
        {
            auto sum = *i;
            if (sum == expected_sum) std::cout << "{" << sum << "}" << std::endl;
            for(auto j = i+1; j != v.end(); j++ )
            {
                sum = sum + *j;
                auto print = [&](){
                    // print
                    std::cout << "{";
                    for (auto k = i; k <= j; k++)
                    {
                        std::cout << *k << " , ";
                    }
                    std::cout << "}" << std::endl;
                };
                if ( sum == expected_sum) print();
            }
        }
    }

}

//keep track of sum , if sum is seen before, that means range from index where sum was seen to this index is the range to print
//from quora
void print_subarray_with_sum(const std::vector<int>& v, int sum)
{
    // sum to index map
    std::unordered_multimap<int,int> sum_to_index_map;
    sum_to_index_map.insert({sum , -1});

    auto sum_so_far = sum;
    for (auto i = 0 ; i< v.size(); ++i)
    {
        sum_so_far+= v[i];
        
        // equal range returns pair (begin and end) of values
        auto range_of_indexes = sum_to_index_map.equal_range(sum_so_far-sum);
    
        for (auto it = range_of_indexes.first; it != range_of_indexes.second; ++it)
        {
            std::cout << "[" << (it->second)+1 << "," << i << "]" <<  std::endl;
        }
        sum_to_index_map.insert({sum_so_far,i});
    }
}

int main()
{

    std::vector<int> v { 0 };
    //crude::print_subarray_with_sum(v,0);
    print_subarray_with_sum(v,0);

    std::cout << "=============" << std::endl;

    std::vector<int> v11 { 1 };
    print_subarray_with_sum(v,1);

    std::cout << "=============" << std::endl;

    std::vector<int> v1 { 4, 2, -3, -1, 0, 4 };
    //crude::print_subarray_with_sum(v1,0);
    print_subarray_with_sum(v1,4);

    std::cout << "=============" << std::endl;
    
    std::vector<int> v2 { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
    //crude::print_subarray_with_sum(v2,0);
    print_subarray_with_sum(v2,0);

    std::cout << "=============" << std::endl;
    
    std::vector<int> v4 { 4,0,4,0 };
    //crude::print_subarray_with_sum(v2,0);
    print_subarray_with_sum(v4,4);

    return 0;
}

#include <iostream>
#include <unordered_set>
#include <cassert>
#include <vector>
#include <stdlib.h>


// http://www.techiedelight.com/find-maximum-length-sub-array-equal-number-0s-1s/


namespace std_inspired
{
    template<class ForwardIterator, class OldValue, class NewValue>
    void replace_if(ForwardIterator begin, const ForwardIterator& end, const OldValue& old_value, const NewValue& new_value)
    {
        while ( begin < end)
        {
            if (*begin == old_value)
            {
                *begin = new_value;
            }

            begin++;
        }
    }
}

class MaxUniqueSubArray
{
    public:
        
        // The idea is to replace 0 with -1 , and find a subarray with sum = 0
        // The alogrithm to find subarray with sum =0 has a complexity of O(N)
        // Hence overall complexity of this problem is O(N)

        static int find(const std::vector<int>& v)
        {
            // Lets first make a copy of original vector.
            // This could be expensive, but if you have liberty to use the original
            // vector , should use original vector without copy.
            std::vector<int> v1(v);

            // This is std inspired implementation of replace_if
            std_inspired::replace_if(v1.begin(),v1.end(), 0, -1);

            // Code to find the max_subarray with sum = 0
            std::unordered_set<int> m(0);
            auto sum = 0;
            auto count = 0, max_count = 0;
            for (auto i=0u; i < v1.size(); i++)
            {
                sum+= v1[i];
                if (m.find(sum) != m.end())
                {
                    count += 1;
                    if (count > max_count)
                    {
                        max_count = count;
                    }
                }
                else
                {
                    count = 0;
                }

                m.insert(sum);
            }

            return max_count;
        }

};


int main()
{
    // Test case 1
    std::vector<int> v{ 0, 0, 1, 0, 1, 0, 0 };
    assert(MaxUniqueSubArray::find(v) == 4 );
    
    char ch;
    std::cin >> ch;

    return 0;
}

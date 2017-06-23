/* This is the first time i will be using an unordered map

*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

class BinarySortInLinearTime
{
    public:
        // Complexity : O(N)
        static void sort(std::vector<int>& v) {
            auto size = v.size();
            auto count = 0u;

            for (const auto& elem : v) {
                if (elem == 1) count++;
            }
            
            for (auto i = 0u; i < size ; ++i) {
                v[i] = i < count ? 1 : 0;
            }
        }

        // Linear time sort
        static void sort_efficient(std::vector<int>& v) {
            auto i =0u, j =0u;
            const auto size = v.size();
            for (i = 0; i < size; ++i)
            {
                if (v[i] == 1)
                    v[j++] = 1;
            }

            while(j < size)
            {
                v[j++] = 0;
            }
        }

        static void print(const std::vector<int> &v) {
            for (const auto element : v)
                std::cout <<  element << " ";
            
            std::cout << std::endl;
        }
};

class RearrangeOddEvenInLinearTime
{
    public:
    static void arrange(std::vector<int>& v)
    {
        auto j = 0u;
        auto size = v.size();
        
        for (auto i=0u;i<size;i++)
        {
            if (v[i] % 2 != 0)
            {
                std::swap(v[i], v[j++]);
            }
        }
    }

};

int main() {
    std::vector<int> arr { 1,1,1,1,1,0,0,0,0,0 };
    BinarySortInLinearTime::sort_efficient(arr);
    BinarySortInLinearTime::print(arr);

    std::vector<int> arr1 { 1,1,1,1,1,0,0,0,0,0 };
    BinarySortInLinearTime::sort(arr1);
    BinarySortInLinearTime::print(arr1);

    std::vector<int> arr3 {1,2,3,4,5,6,7,8,9,10};
    RearrangeOddEvenInLinearTime::arrange(arr3);
    std::vector<int> expected_arr = {1,3,5,7,9,2,4,6,8,10};
    BinarySortInLinearTime::print(arr3);
    assert(std::is_permutation(expected_arr.begin(),expected_arr.end(),arr3.begin()));

    char ch;
    std::cin >> ch;
    return 0;

}



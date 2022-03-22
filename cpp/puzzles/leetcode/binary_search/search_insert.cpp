// https://leetcode.com/problems/search-insert-position/

// binary_search

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    static int searchInsert(vector<int>& nums, int target) {
        if (target < nums[0]) return 0;
        int e = nums.size() - 1;
        if (target > nums[e]) return e+1;

        int b = 0;
        while (b <= e)
        {
           int m = b + ( e - b ) / 2;
           if (nums[m] == target) return m;
           if (nums[m] < target)
           {
               b = m+1;
           }
           else
           {
               e = m-1;
           }
        }
        return b;
    }
};


int main()
{
    {
        std::vector<int> v {1,3,5,6};
        assert(Solution::searchInsert(v,5) == 2);
    }
    
    {
        std::vector<int> v {1,3,5,6};
        assert(Solution::searchInsert(v,2) == 1);
    }

    {
        std::vector<int> v {1,3,5,6};
        assert(Solution::searchInsert(v,7) == 4);
    }

    {
        std::vector<int> v {1,3,5,6};
        assert(Solution::searchInsert(v,0) == 0);
    }

    {
        std::vector<int> v {1};
        assert(Solution::searchInsert(v,1) == 0);
    }

}
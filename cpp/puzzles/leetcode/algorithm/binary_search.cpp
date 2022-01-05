//https://leetcode.com/problems/binary-search/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    static int search(vector<int>& nums, int target) {
        int b = 0;
        int e = nums.size() - 1;
        while(b <= e)
        {
            int m = b + (e-b)/2;
            if (nums[m] == target) return m;
            if (nums[m] < target) b = m + 1;
            else if (nums[m] > target) e = m - 1;
        }

        return -1;
    }
};

int main()
{
    {
        std::vector<int> v{-1,0,3,5,9,12};
        assert(Solution::search(v,9) == 4);
    }

    {
        std::vector<int> v{-1,0,3,5,9,12};
        assert(Solution::search(v,2) == -1);
    }

    {
        std::vector<int> v{5};
        assert(Solution::search(v,5) == 0);
    }

    {
        std::vector<int> v{5};
        assert(Solution::search(v,-5) == -1);
    }

    return 0;
}
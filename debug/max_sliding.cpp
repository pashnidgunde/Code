//https://leetcode.com/problems/sliding-window-maximum/
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (k<=1) return nums;
        std::map<int,int, std::greater<int>> m;
        for (size_t i = 0; i<k; i++)
        {
            m[nums[i]] ++;
        }
        std::vector<int> r;
        auto it = nums.begin();
        // for (size_t i=k; i<=nums.size(); i++)
        // {
        //     r.push_back(m.begin()->first);
            
        //     m[*it]--;
        //     if (m[*it] == 0)
        //         m.erase(m[*it]);
        //     it++;

        //     m[nums[i]]++;
        // }

        for (size_t i=k; i<=nums.size(); i++)
        {
            r.push_back(m.begin()->first);
            
            m[*it]--;
            if (m[*it] == 0)
                m.erase(m[*it]);
            it++;

            m[nums[i]]++;
        }
        return r;
    }
};

int main()
{
    {
        Solution s;
        std::vector<int> i{1,3,-1,-3,5,3,6,7}; // [1,3,-1,-3,5,3,6,7]
        std::vector<int> e{3,3,5,5,6,7};
        auto v = s.maxSlidingWindow(i,3);
        assert((v==e));
    }

    {
        Solution s;
        std::vector<int> i{9,11};
        std::vector<int> e{11};
        auto v = s.maxSlidingWindow(i,2);
        assert((v==e));
    }

    return 0;
}
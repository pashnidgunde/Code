// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

// binary search
// std::lower_bound

#include <vector>
#include <cassert>

using namespace std;
class Solution1 {
public:
    int find_pos(vector<int>& nums, int target, int b, bool first)
    {
        int e = nums.size() - 1;
        int first_pos = -1;
        while ( b <= e)
        {
            int mid = b + (e - b) / 2;
            if (nums[mid] == target)
            {
                 first_pos = mid;
                 if (first)
                    e = mid -1;
                 else
                    b = mid + 1;
                 continue;
            }
            if (nums[mid] > target)
            {
                 e = mid - 1;
            }
            else
            {
                b = mid + 1;
            }
        }
        
        return first_pos;
    }
    
    vector<int> searchRangeTraditional(vector<int>& nums, int target) {
        // This solution can short circuit in case we dont have a target in range
        auto first_pos = find_pos(nums,target, 0, true);
        if (first_pos ==  -1) return { -1, -1};
        auto last_pos = find_pos(nums,target, first_pos, false);
        return {first_pos, last_pos};
    }
};

class Solution {
public:
    // influence with idea to share code and find n in range first occurance and then find range n+1
    int find_pos(vector<int>& nums, int target)
    {
        int size = nums.size();
        int e =  size - 1;
        int first_pos = size;
        int b = 0;
        int mid = 0;
        while ( b <= e)
        {
            mid = b + (e - b) / 2;
            // find first occurance of number greater or equal to target
            if (nums[mid] >= target)
            {
                first_pos = mid; 
                e = mid - 1;
            }
            else 
            {
                b = mid + 1; 
            }
        }
        
        return first_pos;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        auto first_pos = find_pos(nums,target);
        auto last_pos = find_pos(nums,target+1);
        return (first_pos < last_pos) ?
            std::vector<int>{first_pos, last_pos - 1} : std::vector<int>{ -1, -1};
    }
};

class SolutionStdAlgo {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto first_pos = std::lower_bound(nums.begin(),nums.end(),target);
        auto last_pos = std::lower_bound(nums.begin(),nums.end(),target+1);
        if (first_pos < last_pos)
        {
            auto d_f = (int)std::distance(nums.begin(),first_pos);
            auto d_e = (int)std::distance(nums.begin(),last_pos);
            return std::vector<int>{d_f, d_e-1};
        }
        return std::vector<int>{ -1, -1};
    }
};

int main()
{
    {
        {
            Solution1 s1;
            Solution s;
            std::vector<int> i = {5,7,7,8,8,10};
            auto r = s1.searchRangeTraditional(i,8);
            auto r1 = s.searchRange(i,8);
            assert(r[0] == 3); assert(r[1] == 4);
            assert((r==r1));
            SolutionStdAlgo s2;
            auto r2 = s2.searchRange(i,8);
            assert((r2==r1));
        } 

        {
            Solution s;
            Solution1 s1;
            std::vector<int> i = {5,7,7,8,8,10};
            auto r = s1.searchRangeTraditional(i,6);
            auto r1 = s.searchRange(i,6);
            assert(r[0] == -1); assert(r[1] == -1);
            assert((r==r1));
            SolutionStdAlgo s2;
            auto r2 = s2.searchRange(i,6);
            assert((r2==r1));
        } 

        {
            Solution1 s1;
            Solution s;
            std::vector<int> i = {};
            auto r = s1.searchRangeTraditional(i,0);
            auto r1 = s.searchRange(i,0);
            assert(r[0] == -1); assert(r[1] == -1);
            assert((r==r1));
            SolutionStdAlgo s2;
            auto r2 = s2.searchRange(i,6);
            assert((r2==r1));
        }
    }
     
}
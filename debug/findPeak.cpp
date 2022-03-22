#include<vector>
#include<climits>

using namespace std;
class Solution {
public:
    
    void findPeak(int begin, int end, vector<int>& nums, int& result)
    {
        if (result != INT_MIN) return;
        if (begin == 0 && end == 0) return;
        if (begin == nums.size() && end == nums.size()) return;
        
        int b = begin;
        int e = end;
        int index = 0;
                
        int le = INT_MAX;
        int re = INT_MAX;
        
        int mid = b + (e-b)/2;
        if (mid <= 0)
        {
            le = INT_MIN;
        }
        else if (mid >= e)
        {
            re = INT_MIN;
        }
        else
        {
            le = nums[mid-1];
            re = nums[mid+1];
        }
        if (nums[mid] > le && nums[mid] > re)
        {
            result = mid;
            return;
        }
        
        findPeak(0,mid,nums,result);
        findPeak(mid+1,e,nums,result);
    }
    
    int findPeakElement(vector<int>& nums) {
        int result = INT_MIN;
        findPeak(0, nums.size()-1,nums, result);
        return result;
    }
};


int main()
{
    Solution s;
    std::vector<int> v{1,2,3,1};
    s.findPeakElement(v);
    return 0;
}
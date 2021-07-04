//https://leetcode.com/problems/container-with-most-water/
#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
    int maxArea(vector<int>& height) {
        size_t begin_index = 0;
        size_t end_index = height.size() - 1;
        
        size_t max_water = 0;
        size_t water_at_two_bars = 0;
        while(begin_index < end_index)
        {
            water_at_two_bars = std::min(height[begin_index], height[end_index]) * (end_index - begin_index);
            max_water = std::max(water_at_two_bars,max_water);
            
            if (height[begin_index] <= height[end_index]) 
            {
                begin_index++;
            }
            else
            {
                end_index--;
            }
        }
        
        return max_water;
    }
};

int main()
{
    Solution s;
    std::vector<int> v {1,8,6,2,5,4,8,3,7};
    s.maxArea(v);
    return 0;
}
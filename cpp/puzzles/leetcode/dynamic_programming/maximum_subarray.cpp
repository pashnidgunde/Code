//https://leetcode.com/problems/maximum-subarray/

// DIVIDE_AND_CONQUER
// DYNAMIC_PROGRAMMING
// KADENS

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    
    int maxSubArray(vector<int>& nums)
    {
        return maxSubArrayKadane(nums);
    }
    
    // Brute force implementation
    int maxSubArrayBruteForce(vector<int>& nums) {
        auto sum = 0, max_sum = INT_MIN;
        for (auto i =0; i <nums.size();  i++)
        {
            sum = 0;
            for (auto j=i; j < nums.size(); j++)
            {
                sum+= nums[j];
                max_sum = std::max(sum,max_sum);
            }
        }

        return max_sum;
    }
    
    // By Kadane algorithm
    int maxSubArrayKadane(vector<int>& nums) {
        auto sum_so_far = 0;
        auto max_sum = INT_MIN;
        for (auto i=0; i < nums.size(); i++)
        {
            sum_so_far += nums[i];
            // if (sum_so_far > max_sum)
            //     max_sum = sum_so_far;
            max_sum = std::max(sum_so_far,max_sum);

            // magic stroke
            //if (sum_so_far < 0)
            //    sum_so_far = 0;
            sum_so_far = std::max(0,sum_so_far);
        }

        return max_sum;
    }

    // By divide and conquer
    int maxSubArrayDivCon(vector<int>& nums) {
        return max_sub_array_divide_and_conquer(nums,0,nums.size()-1);
    }

private:
    int max_sub_array_divide_and_conquer(vector<int>& nums, int b, int e) {
        if (b==e) 
        {
            std::cout << b << "==" << e << " val : " << nums[b] << std::endl;
            return nums[b];
        }
        
        int mid = b + (e-b) / 2;
        
        int max_left = max_sub_array_divide_and_conquer(nums,b,mid);
        std::cout << "b : " << b <<" e : " << e << " mid : " << mid << " max_left : " << max_left << std::endl; 
        int max_right = max_sub_array_divide_and_conquer(nums,mid+1,e);
        std::cout << "b : " << b <<" e : " << e << " mid : " << mid << " max_right : " << max_right << std::endl; 
        int max_over = max_sub_array_over_mid(nums,b,e,mid);
        std::cout << "b : " << b <<" e : " << e << " mid : " << mid << " max_over : " << max_over << std::endl; 

        std::cout << "Max : " << std::max(max_left,std::max(max_right,max_over)) << std::endl;
        std::cout << "------------------------------" << std::endl;
        return std::max(max_left,std::max(max_right,max_over));
    }

    int max_sub_array_over_mid(std::vector<int>& nums,int b, int e,int mid)
    {
        int sum = 0;
        int max_left_sum = INT_MIN;
        for(int i=mid; i >= b; i--)
        {
            sum += nums[i];
            max_left_sum = std::max(sum,max_left_sum);
        }
        
        sum = 0;
        int max_right_sum = INT_MIN;
        for(int i=mid+1; i <= e; i++)
        {
            sum += nums[i];
            max_right_sum = std::max(sum,max_right_sum);
        }
        
        return std::max(std::max(max_left_sum,max_right_sum),max_left_sum+max_right_sum);
    }
};

int main()
{
    {
        std::vector<int> v {-2,1,-3,4,-1,2,1,-5,4};
        Solution s;
        assert(s.maxSubArray(v) == 6);
        assert(s.maxSubArrayDivCon(v) == 6);
        assert(s.maxSubArrayKadane(v) == 6);
    }

    {
        std::vector<int> v {5,4,-1,7,8};
        Solution s;
        assert(s.maxSubArray(v) == 23);
        assert(s.maxSubArrayDivCon(v) == 23);
        assert(s.maxSubArrayKadane(v) == 23);
    }
}
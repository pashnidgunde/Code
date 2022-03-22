#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <stack>

using namespace std;

    // std::vector<int> v{9,-8};
    // NumArray n(v);
    // n.update(0,3);
    // std::cout <<n.sumRange(1,1);
    // std::cout <<n.sumRange(0,1);
    // n.update(1,-3);
    // std::cout <<n.sumRange(0,1);

    // i : n [9,-8]  m [9, 1]  d[]
    // u : n [3, -8] m [9, 1]  d[0] = -6
    // r : 

class NumArray {
public:
    NumArray(vector<int>& nums) : m_nums(nums)
    {
        m[0] = nums[0];
        for (size_t i=1; i< nums.size(); i++)
        {
            m[i] = m[i-1] + nums[i];
        }
    }
    
    void update(int index, int val) {
        d[index]=val-m_nums[index];
        m_nums[index] = val;
    }
    
    int sumRange(int left, int right) {
        if (left == right) return m_nums[left];
        int ln = (left == 0) ? m[left] : m[left] - m[left-1];
        int total = m[right] - ln;
        for(const auto& e : d)
        {
            if (e.first >= left && e.first <= right)
            {
                total += e.second;
            }
        }
        return total;
    }
    
    std::vector<int> m_nums;
    std::unordered_map<int, long> m;
    std::map<int,long> d;
};

int main()
{
    {
        std::vector<int> v{9,-8};
        NumArray n(v);
        n.update(0,3);
        std::cout <<n.sumRange(1,1);
        std::cout <<n.sumRange(0,1);
        n.update(1,-3);
        std::cout <<n.sumRange(0,1);
    }

    {
        std::vector<int> v{-1};
        NumArray n(v);
        std::cout <<n.sumRange(0,0);
        n.update(0,1);
        std::cout <<n.sumRange(0,0);
    }

    
    
    return 0;
}


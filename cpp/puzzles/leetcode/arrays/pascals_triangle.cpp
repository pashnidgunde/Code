//https://leetcode.com/problems/pascals-triangle/
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        std::vector<vector<int>> r;
        std::vector<int> first;
        first.push_back(1);
        r.emplace_back(first);
        for (int i = 1; i< numRows; i++)
        {
            r.push_back({});
            auto & cv = r[i];
            cv.resize(i+1);
            cv[0] = 1;
            
            int j = 1;
            auto & pv = r[i-1];
            for (int k = 0; k < pv.size() - 1; k++)
            {
                cv[j] = pv[k] + pv[k+1];
                j++;
            } 

            cv[cv.size() -1] = 1;
        }
        return r;
    }
};

int main()
{
    Solution s;
    auto r = s.generate(5);
    //assert({{1},{1,1},{1,2,1},{1,3,3,1},{1,4,6,4,1}})
    return 0;
}
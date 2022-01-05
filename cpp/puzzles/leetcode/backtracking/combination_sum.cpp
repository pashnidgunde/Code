//https://leetcode.com/problems/combination-sum/
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
public:

    void print(const vector<int>& candidates, int index, int target, vector<int>&ir , vector<vector<int>>& r)
    {
        for (int i= 0; i< index; i++)
        {
            std::cout << "  ";
        }

        std::stringstream ss;
        ss << "target : " << target
            << ", i : " << index
            << ", e: " << candidates[index]
            << ", ir : " ;

        auto print_vector = [&](auto& ir){
            std::stringstream s;
            s << " [";
            for (const auto & elem : ir)
            {
                s << elem << " ,";
            }
            s << " ] ,";
            ss << s.str();
         };
        print_vector(ir);

        ss << " r : " ;
        for (const auto& v : r)
        {
            print_vector(v) ;
        }
        
        std::cout << ss.str() << std::endl;
    }

    void backtrack(const vector<int>& candidates, int start, int target, vector<int>&ir , vector<vector<int>>& r)
    {
        //print(candidates,start,target, ir,r);

        if (target < 0)
            return;

        if (target == 0)
        {
            r.push_back(ir);
            print(candidates,start,target, ir,r);
        }

        for (size_t i = start; i< candidates.size(); i++)
        {
            ir.push_back(candidates[i]);
            //print(candidates,i,target, ir,r);
            backtrack(candidates,i,target-candidates[i],ir,r);
            ir.pop_back();            
            //print(candidates,i,target, ir,r);
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> r;
        vector<int> ir;
        backtrack(candidates,0,target,ir,r);
        
        return r;
    }
};

int main()
{
    {
        Solution s;
        std::vector<int> i{2,3,6,7};
        auto result = s.combinationSum(i, 7);
    }
    
    return 0;
}
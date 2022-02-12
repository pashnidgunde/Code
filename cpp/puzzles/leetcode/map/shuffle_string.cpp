//https://leetcode.com/problems/shuffle-string/
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        std::map<int,char> m;
        for(int i = 0; i< s.size(); i++)
        {
            m[indices[i]] = s[i];
        }
        
        for (auto& e : m)
        {
            s[e.first] = e.second;
        }
        
        return s;
    }
};

int main()
{
    Solution s;
    std::vector<int> v{4,5,6,7,0,2,1,3};
    assert(s.restoreString("codeleet", v) == std::string("leetcode"));
    return 0;
}
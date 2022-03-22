//https://leetcode.com/problems/repeated-substring-pattern/
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;
class Solution {
public:
    
    bool is_rep_ss(const std::string& ss, const std::string& s)
    {
        if (s.size() % ss.size() != 0) return false;
        int bs = ss.size();
        while (bs < s.size())
        {
            //std::cout << s.substr(bs,substr.size()) << std::endl;
            if (ss != s.substr(bs,ss.size()))
                return false;

            bs += ss.size();
        }
        return true;
    }
    
    bool repeatedSubstringPattern(string s) {
        if (s.empty()) return false;
        if (s.size() == 1) return false;
        
        std::string ss ="";
        for (int i=0; i < s.size()/2 ; i++)
        {
            ss += s[i];
            if (is_rep_ss(ss, s))
                return true;
        }

        return false;
    }
};

int main()
{
    Solution s;
    assert(s.repeatedSubstringPattern("abcabcabcabc") == true);
}
//https://leetcode.com/problems/remove-outermost-parentheses/
#include <cassert>
#include <string>

using namespace std;

class Solution {
public:
    string removeOuterParentheses(string s) {
        int index = -1;
        int lp = 0;
        int rp = 0;
        for (int i = 0; i< s.size(); i++)
        {
            if (s[i] == '(')
            {
                if (index == -1)
                {
                    index = i;
                }
                lp++;
            }
            else
            {
                rp++;
                if (lp == rp)
                {
                    s.erase(i, 1);
                    s.erase(index, 1);
                    index = -1;
                    i -= 2 ;
                }
            }
        }
        return s;
    }
};

int main()
{
    Solution s;
    assert(s.removeOuterParentheses("(()())(())") == std::string("()()()"));
    assert(s.removeOuterParentheses("(()())(())(()(()))") == std::string("()()()()(())"));
    assert(s.removeOuterParentheses("()()") == std::string(""));
    return 0;
}
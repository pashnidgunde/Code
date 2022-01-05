//https://leetcode.com/problems/valid-palindrome-ii/
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
class Solution {
public:
    bool validPalindrome(string s) {
        auto isAlmostPalindrome = [] (std::string::iterator begin, std::string::iterator end, int skip_count, bool skip_start ) {
            int skipped = 0;
            while(begin < end) 
            {
                if (*begin != *end)
                {
                    if (skipped == skip_count) return false;
                    if (skip_start) 
                        begin++;
                    else
                        end--;
                    
                    skipped++;
                    continue;
                }
                begin++;
                end--;
            }
            return true;    
        };
        
        return isAlmostPalindrome(s.begin(),s.end()-1,1, true) || isAlmostPalindrome(s.begin(),s.end()-1,1, false);
    }
};


int main()
{
    Solution s;
    assert((s.validPalindrome("aba")));
    assert(s.validPalindrome("abca"));
    assert(!s.validPalindrome("abc"));
    assert(s.validPalindrome("deeee"));
    assert(s.validPalindrome("eeeed"));
    assert(s.validPalindrome("cbbcc"));
    return 0;
}
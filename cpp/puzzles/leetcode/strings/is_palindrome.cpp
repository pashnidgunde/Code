//https://leetcode.com/problems/palindrome-number/

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <cassert>
#include <vector>
#include <sstream>

class Solution {
    public:

    bool isPalindrome(std::string s)
    {
        int b = 0;
        int e = s.length() -1;
        
        while (b <= e)
        {
            if (s[b] != s[e])
                return false;
            
            b++;
            e--;
        }
        return true;
    }
    
    bool isPalindrome(int x) {
        std::stringstream s;
        s << x;
        std::string str =  s.str();
        return isPalindrome(str);
    }
};

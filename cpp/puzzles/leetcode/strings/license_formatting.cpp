// https://leetcode.com/problems/license-key-formatting/
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
        int e = s.size()-1;
        int kk = k;
        std::stringstream ss;
        while (e >= 0)
        {
            if (std::isalnum(s[e]))
            {
                ss << char(std::toupper(s[e]));
                kk--;
                if (kk == 0)
                {
                    ss << "-";
                    kk = k;    
                }
            }
            e--;
        }
        
        std::string r = ss.str();
        if (r[r.size()-1] == '-') r.erase(r.size()-1, 1);
        std::reverse(r.begin(), r.end());
        std::cout << r << std::endl;
        return r;
    }
};

int main()
{
    Solution s;
    assert(s.licenseKeyFormatting("5F3Z-2e-9-w", 4) == "5F3Z-2E9W");
    
    return 0;
}
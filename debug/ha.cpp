


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

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) 
    {
        std::map<int,pair<int,int>> t;
        std::string s = "";
        int level = -1;
        int max = 0;
        for (size_t i = 0; i< input.length(); i++)
        {
            if ( input[i] == '\n' )
            {
                i++;
                level = -1;
                while(input[i] == '\t') 
                {
                    i++;
                    level++;
                }

                int pl = std::max(level - 1, 0);
                if (s[s.back()-4] == '.')
                {
                    t[level] = {t[pl].first,t[pl].second + s.size()};
                    max = t[pl].second + s.size();
                }
                else
                {
                    t[level] = {t[pl].first + s.size(),t[pl].first};
                }
                s="";
            }
            else
            {
                s = s + input[i];
            }
        }

        return 32;
    }
};

int main()
{
    Solution s;
    assert(s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") == 32);
    // assert(s.addStrings("456", "77") == "533");
    // assert(s.addStrings("0", "0") == "0");
    
    return 0;
}


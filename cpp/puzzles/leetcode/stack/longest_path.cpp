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

//assert(s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") == 32);

class Solution {
public:

    int lengthLongestPath(string input) 
    {
        std::string s = "";
        size_t m = 0;
        std::stack<size_t> d;
        for (size_t i = 0; i< input.length();i++)
        {
            if (input[i] != '\n')
            {
                s = s + input[i];
            }
            
            if ( input[i] == '\n' || i == input.length() - 1)
            {
                i++;
                if (s.find('.') == s.npos)
                {
                    d.push((!d.empty() ? d.top() : 0) + s.size() + 1);
                    //std::cout << "str : " << s << " : " << d.top() << std::endl;
                }
                else
                {
                    if (!d.empty())
                        m = std::max(m, d.top() + s.size());
                    else
                        m = std::max(m, s.size());
                    //std::cout << "str : " << s << " : " << d.top() << " max : " << m << std::endl;
                }

                int level = 0;
                while(input[i] == '\t')
                {
                    level++;
                    i++;
                }
                i--;

                //std::cout << "level : " << level << ", stack size : " << d.size() << std::endl;
                while(d.size() > level)
                {
                    //std::cout << "Popping out :" << d.top() << std::endl;
                    d.pop();
                }

                s="";
            }
            
        }

        return m;
    }
};

int main()
{
    Solution s;
    assert(s.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") == 32);
    assert(s.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext") == 20);
    
    
    return 0;
}


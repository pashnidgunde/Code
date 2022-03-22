#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <regex>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string mostCommonWord1(string paragraph, vector<string>& banned) {
        std::unordered_set<std::string> ub(banned.begin(), banned.end());
        std::transform(paragraph.begin(), 
                       paragraph.end(), 
                       paragraph.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        
        std::unordered_map<std::string, size_t> tokens;
        
        std::regex rgx{R"(\w+)"}; // split for words
        regex_iterator<string::iterator> it(paragraph.begin(), paragraph.end(), rgx);
        regex_iterator<string::iterator> end;

        for (; it != end; ++it)
        {
            //cout << it->str() << endl;
            if (ub.find(it->str()) == ub.end())
            {
                tokens[it->str()] ++;
            }
        }
        
        auto max = std::max_element(tokens.begin(),
                                    tokens.end(),
                                    [] (const auto& a, const auto& b)
                                        { return a.second < b.second; } );
        return max->first;
    }
    
    string mostCommonWord(string paragraph, vector<string>& banned) {
        std::unordered_set<std::string> ub(banned.begin(), banned.end());
        std::unordered_map<std::string, size_t> r;
        
        std::string sub_string;
        for (char c : paragraph)
        {
            if (isalpha(c))
            {
                sub_string += tolower(c);
            }
            else
            {
                if (!sub_string.empty() && ub.find(sub_string) == ub.end())                
                {
                    r[sub_string]++;
                }
                sub_string = "";
            }
        }
        
        if (r.empty()) return sub_string;
        
        auto it = std::max_element(r.begin(),r.end(),
                         [](const auto& lhs, const auto& rhs)
                         {
                             return lhs.second < rhs.second;
                         });
        
        return it->first;
    }
};

int main()
{
    std::unordered_map<int,int> m {{1,1}};
    auto it = std::max_element(m.begin(), m.end(), [](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; });
    std::cout << it->first;
}

/*
int main()
{
string seq = "Some words. And... some punctuation.   ";
regex rgx("(\\w+)");

regex_iterator<string::iterator> it(seq.begin(), seq.end(), rgx);
regex_iterator<string::iterator> end;

for (; it != end; ++it)
{
    cout << it->str() << endl;
}

return 0;
}

*/

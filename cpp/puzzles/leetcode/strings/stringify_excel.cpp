#include<string>
#include<cassert>
#include<vector>
#include<unordered_map>
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>

class Solution
{
    public:
    std::string stringify(int i)
    {
        std::unordered_map<int, char> m;
        m[1] = 'A';
        for (int i=2; i<=26 ; i++)
        {
            m[i] = 'A' + i -1;
        }

        std::stringstream ss;
        int number = i;
        int remainder = 0;
        while(number > 0)
        {
            remainder = number % 26;
            ss << m[remainder];
            number = number / 26;
        }

        auto s = ss.str();
        std::reverse(s.begin(),s.end());
        return s;

    }
};

// [1,3,3,6,6,7,9]
// [2,3,5,7]
// [1,2,5,6,6,9]
int main()
{
    Solution s;
    std::string r = s.stringify(56);
    std::cout << r;
    
    return 0;
}


/*
A,B,....Z,[AA,AB,AZ],BA,BB,...BZ,...ZZ, AAA,AAB, ...ZZZ;

A = 1
Z = 26
AA = 27 = 26 + 1
AB = 28 = d = 1, r = 2
BA = 56 d =2  */
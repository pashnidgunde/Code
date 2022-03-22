//https://leetcode.com/problems/add-strings/

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <cassert>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    string addStrings(string num1, string num2) {
        auto rb1 = num1.rbegin();
        auto rb2 = num2.rbegin();
        auto re1 = num1.rend();
        auto re2 = num2.rend();
        
        int d = 0;
        int c = 0;
        
        std::stringstream s;
        while(rb1 != re1 || rb2 != re2)
        {
            d = ((rb1 == re1) ? 0 : int(*rb1) - '0')  + ((rb2 == re2) ? 0 : int(*rb2) - '0') + c;
            c =  d/10;
            d = d % 10;
            
            s << d;
            
            if (rb1 != re1) rb1++;
            if (rb2 != re2) rb2++;
        } 
        
        if (c > 0) s << c;
         
        std::string r = s.str();
        std::reverse(r.begin(), r.end());
        //std::cout << r << std::endl;
        return r;
    }

    // string addStrings(string num1, string num2) {
    //     auto rb1 = num1.rbegin();
    //     auto rb2 = num2.rbegin();
    //     auto re1 = num1.rend();
    //     auto re2 = num2.rend();
        
    //     int d = 0;
    //     int c = 0;
        
    //     std::stringstream s;
    //     while(rb1 != re1 && rb2 != re2)
    //     {
    //         d = int(*rb1) - '0'  + int(*rb2) - '0';
    //         c =  d/10;
    //         d = d % 10;
            
    //         s << d;
    //     } 

    //     auto sum = [&](auto rb,auto re)
    //     {
    //         while (rb1 != re1) 
    //         {
    //             d = int(*rb1) - '0' + c;            
    //             c =  d/10;
    //             d = d % 10;
    //             s << d;   
    //         }
    //     };

    //     sum(rb1,re1);
    //     sum(rb2,re2);

    //     if (c > 0) s << c;
         
    //     std::string r = s.str();
    //     std::reverse(r.begin(), r.end());
    //     //std::cout << r << std::endl;
    //     return r;
    // }

};
int main()
{
    Solution s;
    assert(s.addStrings("11", "123") == "134");
    assert(s.addStrings("456", "77") == "533");
    assert(s.addStrings("0", "0") == "0");
    
    return 0;
}


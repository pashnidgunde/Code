#include <iostream>
#include <cassert>
#include <cmath>



class Solution {
public:
    bool isPalindrome_(int x) {
        if ( x < 0 ) return false;
        int x_copy = x;
        int dn = x;
        int rn = x;

        auto digits = 0;
        while (x_copy > 0)
        {
            x_copy /= 10;
            digits++;
        }
        
        int divider = powl(10,digits-1);
        int rr = 0;
        int dr = 0;
        while(divider > 0)
        {
            dr = dn / divider;
            rr = rn % 10;
            if (dr != rr) return false;

            dn = dn - dr * divider;
            divider = divider / 10;
            rn = rn / 10;            
        }

        return true;
    }

    int isPalindrome(int x)
    {
        int reverse_x = 0;
        int x_copy = x;
        int mul = 1;
        while(x_copy > 0)
        {
            reverse_x = reverse_x * mul + x_copy % 10;
            mul = mul * 10;
            x_copy = x_copy / 10;
        }

        return x == reverse_x;
    }
};

int main()
{
    Solution s;
    assert(!s.isPalindrome(-121));
    assert(s.isPalindrome(121));
    assert(!s.isPalindrome(10));
    assert(s.isPalindrome(9999));
    assert(s.isPalindrome(99599));
    return true;
}


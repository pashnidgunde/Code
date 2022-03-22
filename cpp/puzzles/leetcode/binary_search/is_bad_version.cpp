//https://leetcode.com/problems/first-bad-version/
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

// binary_search

#include <iostream>
#include <cassert>

class Solution {
public:

    static bool isBadVersion(int num)
    {
        std::cout << "isBadVersion(" << num << ")" << std::endl;
        return num == 4;
    }

    static int firstBadVersion(int n) {
        int b = 1;
        int e = n;
        int m = n;

        int lb = e;
        
        while (b <= e)
        {
            m = b + (e - b) / 2;
            if (isBadVersion(m))
            {
                lb = m;
                e = m - 1;
            }
            else
            {
                b = m + 1;
            }
        }
     
        return lb;
    }
};

int main()
{
    assert(Solution::firstBadVersion(5) == 4);
}
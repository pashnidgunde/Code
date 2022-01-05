// https://leetcode.com/problems/fibonacci-number/

#include <iostream>
#include <cassert>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int fib(int n) {
        auto n0 =0;
        if (n == 0) return n0;

        auto n1 =1;
        if (n == 1) return n1;

        auto n2=0;
        for(int i=2; i<=n;i++)
        {
            n2 = n1 + n0;
            n0 = n1;
            n1 = n2;
        }

        return n2;

    }

    int fib_rec(int n)
    {
        if (n==0) return 0;
        if (n==1) return 1;

        return fib_rec(n-1) + fib_rec(n-2);
    }

    // constructor
    Solution()
    {
        m_lookup[0] = 0;
        m_lookup[1] = 1;
    }

    int fib_rec_dp(int n)
    {
        if (m_lookup.find(n) != m_lookup.end()) return m_lookup[n];
        
        auto fib_n = fib_rec_dp(n-1) + fib_rec_dp(n-2);
        m_lookup[n] = fib_n;
        
        return fib_n;
    }

private:
    std::unordered_map<int,int> m_lookup;
};
 
int main()
{
    {
        Solution s;
        assert(s.fib(4) == 3);
        assert(s.fib_rec(4) == 3);
        assert(s.fib_rec_dp(4) == 3);
    }

    {
        Solution s;
        assert(s.fib(3) == 2);
        assert(s.fib_rec(3) == 2);
        assert(s.fib_rec_dp(3) == 2);
    }

    {
        Solution s;
        assert(s.fib(2) == 1);
        assert(s.fib_rec(2) == 1);
        assert(s.fib_rec_dp(2) == 1);
    }
}
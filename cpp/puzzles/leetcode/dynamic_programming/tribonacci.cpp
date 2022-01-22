#include<unordered_map>
#include <cassert>
class Solution {
public:
    int tribonacci(int n) {
        if (m_lookup.find(n) != m_lookup.end()) return m_lookup[n];
        auto tribonacci_n = tribonacci(n-3) + tribonacci(n-2) + tribonacci(n-1);
        m_lookup[n] = tribonacci_n;
        return tribonacci_n;
    }

    std::unordered_map<int,int> m_lookup { {0,0}, {1,1}, {2,1}};

};

int main()
{
    Solution s;
    assert(s.tribonacci(25) == 1389537);
    assert(s.tribonacci(4) == 4);
    return 0;

}

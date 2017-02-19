#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int getIthPrime(int i)
{
    auto prime_count = 0;
    auto x = 2;    
    while(1)
    {
        for (j =2 ; j < 10000; ++j)
        {
            auto prime = true;
            for ( x = 2 ; x < j; ++x)
            {
                if ( j %x == 0)
                    prime = false;
            }
            
            if ( prime && (++prime_count == i))
                break;
        }
    }
    
    return j;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    std::cin >> n >> q;
    
    std::stack<int> A;
    
    auto element = 0;
    std::stack<int> x;
    
    for (auto i = 1; i<= n; i++)
    {
        std::cin >> element;
        A.push(element);
        
    }
    
    std::vector<std::stack<int>> B;
    
    for (auto i=0;i<q; i++)
    {
        auto ithPrime = getIthPrime(i+1);
        std::stack<int> b_stack;
        std::stack<int> a_remaining;
        while(A.size())
        {
            int element = A.top();
            if ((element / ithPrime) == 0)
            {
                b_stack.push(element);
            }
            else
            {
                a_remaining.push(element);
            }
        }
        A = a_remaining;
        B.push_back(b_stack);
    }
    
    return 0;
}


//https://www.hackerrank.com/challenges/repeated-string/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup
#include <bits/stdc++.h>

// Notes :
// Order of multiplication and division was very important --> line 24

using namespace std;

/*
 * Complete the 'repeatedString' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. LONG_INTEGER n
 */

long repeatedString(string s, long int n) {
    auto total_count = 0;
    auto remainder = 0;
    if ( n > s.size())
    {
        auto count_of_a = std::count_if(s.begin(), s.end(), [](char ch) {return ch=='a';});
        // order of multiplication and division is very important
        total_count = (n / s.size()) * count_of_a;
        remainder = n % s.size();
    }
    else
    {
        remainder = n;
    }

    total_count += std::count_if(s.begin(), s.begin() + remainder, [](char ch) {return ch=='a';});
    return total_count;
}

int main()
{
    std::cout << repeatedString("aba",10);
    //std::cout << repeatedString("aab",882787);
    //std::cout << repeatedString("gfcaaaecbg",547602);
    std::cout << repeatedString("ababa", 3);
    std::cout << repeatedString("a", 100);

    return 0;
}


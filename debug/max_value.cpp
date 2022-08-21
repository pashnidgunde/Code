#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'maxValue' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY rounds
 */

long maxValue(int n, vector<vector<int>> rounds) {
    std::vector<int> r(n,0);
    int max_value = 0;
    for (const auto& round : rounds)
    {
        auto begin = round[0] - 1;
        auto end = round[1] - 1;
        auto contribution = round[2];
        
        for (int i = begin; i <= end; i++)
        {
            r[i] += contribution;
            max_value = std::max(max_value,r[i]);
        }
    }
    
    return max_value;

}
int main()
{
    std::cout << maxValue(5, {{1,2,100}, {2,5,100}, {3,4,100}});
    return 0;
}


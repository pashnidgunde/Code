#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <regex>
#include <unordered_map>
#include <climits>

using namespace std;

class Solution {
public:

    int cutOffTree(vector<vector<int>>& forest) {
        int steps = 1;
        int r = forest.size();
        int c = forest[0].size();
        
        int i = 0;
        int j = 0;

        vector<vector<bool>> v (r,std::vector<bool>(c, false));
        v[0][0] = true;

        auto next_step = [&](int i, int j) -> std::pair<int,int>
        {
            int next_min = INT_MIN;
            int ni = INT_MIN;
            int nj = INT_MIN;

            // r --> i, j+1
            if ( j+1 < c && !v[i][j+1])
            {
                next_min = forest[i][j+1];
                ni = i;
                nj = j+1;
            }

            // l --> i, j-1
            if (j-1 >= 0 && !v[i][j-1] && next_min > forest[i][j-1])
            {
                next_min = forest[i][j-1];
                ni = i;
                nj = j-1;
            }
            
            // t --> i-1, j
            if (i-1 >= 0 && !v[i-1][j] && next_min > forest[i-1][j])
            {
                next_min = forest[i-1][j];
                ni = i-1;
                nj = j;
            }
            
            // b --> i+1, j
            if (i+1 < r && !v[i+1][j] && next_min > forest[i+1][j])
            {
                next_min = forest[i+1][j];
                ni = i+1;
                nj = j;
            }

            return std::make_pair(ni,nj);

        };

        for (int i = 0; i< r; i++)
        {
            for (int j=0; j<c; j++)
            {
                auto ns = next_step(i,j);
                std::cout << ns.first << ", " << ns.second;
            }
        }
        return steps;
    }
};

int main()
{
    std::vector<std::vector<int>> i {{1,2,3},{0,0,4},{7,6,5}};
    Solution s;
    std::cout << s.cutOffTree(i);

    return 0;
}


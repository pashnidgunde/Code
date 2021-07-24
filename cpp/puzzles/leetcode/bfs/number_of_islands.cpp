// https://leetcode.com/problems/number-of-islands/


#include<vector>
#include<iostream>
#include<cassert>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        size_t r = grid.size();
        size_t c = grid[0].size();
        int islands = 0; 
        for (size_t r1= 0 ; r1 < r; r1++)
        {
            for (size_t c1= 0; c1 < c; c1++)
            {
                if (grid[r1][c1] == '1')
                {
                    islands++;
                    breadth_first_search(r1, c1, r, c, grid);
                }
            }
        }
        return islands;        
    }
private:  
    void breadth_first_search(int r1, int c1, int r, int c, vector<vector<char>>& grid)
    {
        if (r1 < 0 || r1 == r || c1 < 0 || c1 == c || grid[r1][c1] == '0')  return;
        
        grid[r1][c1] = '0';
        
        breadth_first_search(r1,c1+1,r,c,grid);
        breadth_first_search(r1,c1-1,r,c,grid);
        breadth_first_search(r1+1,c1,r,c,grid);
        breadth_first_search(r1-1,c1,r,c,grid);
    }
};

int main()
{
    std::vector<std::vector<char>> grid 
        {{'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}};

    Solution s;
    assert(s.numIslands(grid) == 3);

    std::vector<std::vector<char>> grid1 
    {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };

    assert(s.numIslands(grid1) == 1);
    return 0;
}
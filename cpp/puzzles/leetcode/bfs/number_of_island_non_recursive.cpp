#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:

    void print(const std::vector<std::vector<bool>>& v)
    {
        for (int i=0; i< v.size(); i++)
        {
            for (int j=0; j< v[0].size(); j++)
            {
                std::cout << v[i][j] << ",";
            }
            std::cout << std::endl;
        }
    }

    void bfs(std::vector<std::vector<bool>>& v, std::queue<std::pair<int,int>>& q, const std::vector<std::vector<int>>& c)
    {
        while(!q.empty())
        {
            auto&p = q.front();
            q.pop();
            int i = p.first; int j = p.second;
            v[i][j] = true;

            std::cout << "v[" << i << "]" << "[" << j << "] = " << v[i][j] << std::endl;

            
            
            if (j+1 < v[0].size() && !v[i][j+1] && c[i][j+1]) q.push({i,j+1});
            if (j-1 > 0 && !v[i][j-1] && c[i][j-1]) q.push({i,j-1});
            if (i+1 < v.size() && !v[i+1][j] && c[i+1][j]) q.push({i+1,j});
            if (i-1 > 0 && !v[i-1][j] && c[i-1][j]) q.push({i-1,j});
            
        }
    }

    int findCircleNum(std::vector<std::vector<int>> isConnected) {
        int count =0;
        std::vector<std::vector<bool>> v(isConnected.size(), std::vector<bool>(isConnected.size(), false));
        for (size_t i=0; i< isConnected.size(); i++)
        {
            for (size_t j=0; j<isConnected[0].size(); j++)
            {
                if (!v[i][j] && isConnected[i][j] == 1)
                {
                    count++;
                    std::queue<std::pair<int,int>> q;
                    q.push({i,j});
                    bfs(v,q,isConnected);
                    print(v);
                    std::cout << "-----------" << std::endl;
                }
            }
        }
        return count;
    }
};


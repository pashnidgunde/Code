#include <string>
#include <regex>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <regex>
#include <unordered_map>
#include <climits>
#include <cassert>
#include <queue>

using namespace std;

// class Solution {
// public:

//     int cutOffTree(vector<vector<int>>& forest) {
//         int steps = 0;
//         int r = forest.size();
//         int c = forest[0].size();
        
//         int no_steps = 0;

//         vector<vector<bool>> v (r,std::vector<bool>(c, false));
//         v[0][0] = true;

//         for (int i = 0 ; i < r; i++)
//         {
//             for (int j = 0; j < c; j++)
//             {
//                 if (forest[i][j] == 0)
//                 {
//                     v[i][j] = true;
//                     no_steps++;
//                 }
                
//             }
//         }

//         int next_min = INT_MAX;
//         int ni = 0;
//         int nj = 0;

//         auto next_step = [&](int i, int j) -> std::pair<int,int>
//         {
//             std::cout << "[ " << forest[i][j] << "] --> " ;
//             next_min = INT_MAX;
//             ni = i;
//             nj = j;

//             // r --> i, j+1
//             if ( j+1 < c && !v[i][j+1] && forest[i][j+1] < next_min)
//             {
//                 next_min = forest[i][j+1];
//                 ni = i;
//                 nj = j+1;
//             }

//             // l --> i, j-1
//             if (j-1 >= 0 && !v[i][j-1] && forest[i][j-1] < next_min)
//             {
//                 next_min = forest[i][j-1];
//                 ni = i;
//                 nj = j-1;
//             }
            
//             // t --> i-1, j
//             if (i-1 >= 0 && !v[i-1][j] && forest[i-1][j] < next_min)
//             {
//                 next_min = forest[i-1][j];
//                 ni = i-1;
//                 nj = j;
//             }
            
//             // b --> i+1, j
//             if (i+1 < r && !v[i+1][j] && forest[i+1][j] < next_min)
//             {
//                 ni = i+1;
//                 nj = j;
//             }
            
//             // node visited
//             v[ni][nj] = true;

//             return std::make_pair(ni,nj);
//         };

//         int i = 0;
//         int j = 0;

//         while(true)
//         {
//             auto ns = next_step(i,j);
//             if (ns.first == i && ns.second == j) break;
//             i = ns.first;
//             j = ns.second;
//             steps++;
//         } 
//         std::cout << std::endl;
//         if (steps == 0) return -1;
//         return (steps == r*c - no_steps - 1) ? steps : -1;
//     }
// };

class Solution {
public:
    typedef pair<int, pair<int, int>> d;
    int cutOffTree(vector<vector<int>>& forest) {
        priority_queue<d, vector<d>, greater<d>> q; // store tree height and its indexes pair
        int res=0;
        for(int i=0; i<forest.size();i++)
            for(int j=0;j<forest[0].size();j++)
                if(forest[i][j]>1) q.push({forest[i][j], {i, j}});
        int i=0, j=0; // starting index
        
        vector<vector<bool>> qualified; // mask each grid by whether it can be walked through or not
        for(int i=0; i<forest.size();i++){
            vector<bool> v;
            for(int j=0;j<forest[0].size();j++){
                if(forest[i][j]==0) v.push_back(false);
                else v.push_back(true);
			}
            qualified.push_back(v);
        }
        
        while(!q.empty()){
            d tree=q.top();
            q.pop();
            int step=0;
            int h=tree.first, k=tree.second.first, l=tree.second.second;
            helper(forest, i, j, k, l, step, qualified); // (i,j) current position; (k,l) target position
            i=k, j=l; // set current to target once the target tree has been cut off
            if(step==-1) return -1; 
            else res += step;
            
        }
        return res;
    }
    
    void helper(vector<vector<int>>& forest, int i, int j, int k, int l, int& step, vector<vector<bool>> qualified){
        qualified[i][j]=false;
        queue<pair<int, int>> q; 
        q.push({i, j});
        int i1, j1;
        while(!q.empty()){
            int n=q.size();
            bool flag = true; 
            while(n--){
                pair<int, int> pos = q.front();
                q.pop();
                i1=pos.first, j1=pos.second;
               
                if(i1==k && j1==l) {
                    return; // target reached
                }
                
                if(i1>0 && qualified[i1-1][j1]) {
                    q.push({i1-1, j1});qualified[i1-1][j1]=false;flag =flag &&false;
                }
                if(j1>0 && qualified[i1][j1-1] ){
                    q.push({i1, j1-1});qualified[i1][j1-1]=false;flag =flag &&false;
                }
                if(i1<forest.size()-1 && qualified[i1+1][j1]) {
                    q.push({i1+1, j1});qualified[i1+1][j1]=false;flag =flag &&false;
                }
                if(j1<forest[0].size()-1 && qualified[i1][j1+1] ) {
                    q.push({i1, j1+1});qualified[i1][j1+1]=false;flag =flag &&false; 
                }
            }
            step++;
           
            if(flag) { step =-1;return;} // if no grid of the four directions can be walked through, flag remains true and that indicates we cannot cut off all the trees       
        }
        return; 
    }
};


int main()
{
    Solution s;
    {
        std::vector<std::vector<int>> i {{1,2,3},{0,0,4},{7,6,5}};
        assert(s.cutOffTree(i) == 6);    
    }
    
    {
        std::vector<std::vector<int>> i {{1,2,3},{0,0,0},{7,6,5}};
        assert(s.cutOffTree(i) == -1);    
    }
    
    {
        std::vector<std::vector<int>> i {{2,3,4},{0,0,5},{6,7,8}};
        assert(s.cutOffTree(i) == 6);    
    }

    {
        std::vector<std::vector<int>> i{{54581641,64080174,24346381,69107959},
                                        {86374198,61363882,68783324,79706116},
                                        {668150,92178815,89819108,94701471},
                                        {83920491,22724204,46281641,47531096},
                                        {89078499,18904913,25462145,60813308}};
        assert(s.cutOffTree(i) == 57);    
    }

    return 0;
}


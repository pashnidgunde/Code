// https://leetcode.com/problems/minimum-time-visiting-all-points/
#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
    
        auto& pp = points[0];
        int px = pp[0];
        int py = pp[1];

        int steps = 0;
        std::cout << "Steps to get to [" << px << " , " << py << "] " << steps << std::endl;

        for (int i=1; i< points.size(); i++)
        {
            auto& cp = points[i];
            int cx = cp[0];
            int cy = cp[1];

            int diagonal_steps = std::min(abs(cx - px) , abs(cy - py));
            steps+= diagonal_steps;
            if (px < cx) px += diagonal_steps; else px -= diagonal_steps;
            if (py < cy) py += diagonal_steps; else py -= diagonal_steps;

            if (cx == px) 
            {
                steps+= abs(cy-py);
                if (py < cy) py += abs(cy-py); else py -= abs(cy-py);
            }
            
            if (cy == py) 
            {
                steps+= abs(cx-px);
                if (px < cx) px += abs(cx-px); else px -= abs(cx-px);
            }

            std::cout << "Steps to get to [" << cx << " , " << cy << "] " << steps << std::endl;
        }
        std::cout << "Total steps : " << steps << std::endl;
        std::cout << "------------------------------------------" << std::endl;
        return steps;

    }
};

int main()
{
    Solution s;
    {
        std::vector<std::vector<int>> points{{1,1},{3,4},{-1,0}};
        assert(s.minTimeToVisitAllPoints(points) == 7);
    }
    
    {
        std::vector<std::vector<int>> points{{3,2},{-2,2}};
        assert(s.minTimeToVisitAllPoints(points) == 5);
    }

    {
        std::vector<std::vector<int>> points {{559,511},{932,618},{-623,-443},{431,91},{838,-127},{773,-917},{-500,-910},{830,-417},{-870,73},{-864,-600},{450,535},{-479,-370},{856,573},{-549,369},{529,-462},{-839,-856},{-515,-447},{652,197},{-83,345},{-69,423},{310,-737},{78,-201},{443,958},{-311,988},{-477,30},{-376,-153},{-272,451},{322,-125},{-114,-214},{495,33},{371,-533},{-393,-224},{-405,-633},{-693,297},{504,210},{-427,-231},{315,27},{991,322},{811,-746},{252,373},{-737,-867},{-137,130},{507,380},{100,-638},{-296,700},{341,671},{-944,982},{937,-440},{40,-929},{-334,60},{-722,-92},{-35,-852},{25,-495},{185,671},{149,-452}};
        assert(s.minTimeToVisitAllPoints(points) == 49088 );
    }
    
    return 0;
}
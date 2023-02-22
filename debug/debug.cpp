#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

#include <iostream>

using namespace std;

class Solution {

private:
    
    template<typename Iter>
    [[nodiscard]] std::vector<int> getDiffPerTicket(Iter begin, Iter end) const
    {
        std::vector<int> result;
        result.reserve(std::distance(begin,end));
        for (auto iter = begin; iter !=end; iter++)
        {
            auto& cost = *iter;
            result.emplace_back(cost[0] - cost[1]);
        }
        return result;
    }

public:
    [[nodiscard]] int twoCitySchedCost(vector<vector<int>>& costs) {
        // Algorithm
        // Find total cost for everybody going to A
        auto tc_to_a = std::accumulate(costs.begin(), costs.end(), 0, [](auto tc_to_a, const auto& v) { return tc_to_a + v[0]; });
        // Difference if they went to B
        auto diff = getDiffPerTicket(costs.begin(), costs.end());
        // Sort the differce
        std::partial_sort(diff.begin(), diff.begin() + costs.size()/2, diff.end(), std::greater<int>());
        // for half of them, substract from the total cost
        return std::accumulate(diff.begin(), 
            diff.begin() + costs.size()/2, 
            tc_to_a, 
            [](const auto tc_to_a, const auto cost) { return tc_to_a - cost; });
    }
};

int main()
{
    {
        Solution s;
        std::vector<std::vector<int>> v = {{10,20},{30,200},{400,50},{30,20}};
        auto r = s.twoCitySchedCost(v);
        std::cout << r;
        assert(r == 110);
    }

    return 0;
}
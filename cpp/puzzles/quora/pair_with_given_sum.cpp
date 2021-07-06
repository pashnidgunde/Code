//https://www.techiedelight.com/find-pair-with-given-sum-array/

#include <vector>
#include <cassert>
#include <unordered_set>
#include <optional>

std::optional<std::pair<int,int>> pair_with_given_sum(const std::vector<int>& v, int sum)
{
    std::unordered_set<int> lookup { v.begin() , v.end() };

    for (const auto& elem : v)
    {
        if (lookup.find(sum-elem) != lookup.end() && sum-elem != elem) 
        {
            return std::make_pair(elem, sum-elem);
        }
        
    }
    
    //return std::nullopt;
    return {};
}

int main()
{
    std::vector<int> v { 0,1 };
    assert(pair_with_given_sum(v,1) == (std::pair<int,int>{0,1}));
    assert(pair_with_given_sum(v,2) == std::nullopt );
    
    return 0;
}
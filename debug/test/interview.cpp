
#include <algorithm>
#include <vector>

template<typename Pred>
void sort_by_maginitude(std::vector<std::pair<int,int>>& v, Pred p)
{
    std::sort(v.begin(),
            v.end(),
            //[](const auto&lhs, const auto& rhs) { return (lhs.first / lhs.second) < (rhs.first / rhs.second);  } );
            //[](const auto&lhs, const auto& rhs) { return (lhs.first * rhs.second) < (rhs.first * lhs.second);  } );
            [](const auto&lhs, const auto& rhs) { return p(static_cast<long>(lhs.first * rhs.second), static_cast<long>(rhs.first * lhs.second));  } );
    
}

class ProbMag
{
    public:
    ProbMag(const std::vector<int>& v) 
    {
        _total_size = std::accumulate(v.begin(), v.end(), [](auto& p, total_size_to_reserve) { total_size_to_reserve + p.second;})
    }

    private:
    void init(std::vector<std::pair<int,int>>& v)
    {
        
        //std::vector<int> v1;
        //v1.reserve(total_size_to_reserve);
        
        //for (const auto& e : v)
        //{
        //    for (size_t i=0; i< e.second; i++)
        //        v1.push_back(e.first);
        //}
    }

    int get()
    {
        return v1[std::rand() % v1.size()].first;
    }
};
int main()
{
    
    sort_by_maginitude(v, std::less());
}





[[1,2]]
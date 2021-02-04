#include <unordered_map>
#include <unordered_set>
#include <utility>

struct PairHasher {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2> &pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

int main()
{

    //std::unordered_map<size_t,std::unordered_set<std::pair<size_t,size_t>>> days_to_intersection_map;
    //days_to_intersection_map[0].insert(std::make_pair(0,1));

    std::unordered_set<std::pair<size_t,size_t>,PairHasher> s;
    s.insert(std::make_pair(0,1));


    return 0;
}
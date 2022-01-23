#include <iostream>
#include <unordered_map>

using IntPair = std::pair<int, int>;

struct PairHasher {
  template <typename T1, typename T2>
  size_t operator()(const std::pair<T1, T2> &pair) {
    return std::hash(pair.first) ^ std::hash(pair.second);
  }
};

int main() {
  std::unordered_map<IntPair, bool, PairHasher> my_map;

  return 0;
}
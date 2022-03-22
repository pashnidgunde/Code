#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

struct IsZero {
  bool operator==(const int& elem) { return elem == 0; }
};

template <typename Iter, typename Pred>
int findIndexToReplace(Iter begin, Iter end, Pred p) {}

int main() {
  // std::vector<int> v{0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0};
  std::vector<int> v{0, 1, 0};
  int index_to_replace = findIndexToReplace(v.begin(), v.end(), IsZero());
  std::cout << "Index to replace :: " << index_to_replace;
  assert(index_to_replace == 9);

  return 0;
}

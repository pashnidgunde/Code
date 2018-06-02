
// Move 0's to end
// Approach 1 : O(n) to use linear moving based on non zero element and filing
// up last positions with 0's
#include <vector>
#include "utils.h"

void moveZeroesToEnd(std::vector<int>& v) {
  size_t size = v.size();
  auto k = 0u;
  for (auto i = 0u; i < size; ++i) {
    if (v[i] != 0) {
      v[k++] = v[i];
    }
  }

  while (k < size) {
    v[k++] = 0;
  }
}

void moveZeroesToEndWithPartition(std::vector<int>& v) {
  auto begin = std::begin(v);
  auto end = std::end(v);

  while (begin != end) {
    if (*begin == 0) {
      std::swap(*begin, *end);
      end--;
    }
    begin++;
  }
}

int main() {
  std::vector<int> v{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 5, 6, 7};
  moveZeroesToEnd(v);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));

  std::vector<int> v1{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 5, 6, 7};
  moveZeroesToEndWithPartition(v1);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));
  return 0;
}
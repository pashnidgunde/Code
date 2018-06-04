
// Move elements matching a criterion to the end
// For example move 0's to end
// Approach 1 : O(n) to use linear moving based on non zero element and filing
// up last positions with 0's
//
// This can be achieved with partition as well
//
#include <algorithm.h>  // for partitioning
#include <vector>
#include "algorithm.h"
#include "utils.h"

void moveElementsToEnd(std::vector<int>& v, int element) {
  size_t size = v.size();
  auto k = 0u;
  for (auto i = 0u; i < size; ++i) {
    if (v[i] != element) {
      v[k++] = v[i];
    }
  }

  while (k < size) {
    v[k++] = 0;
  }
}

struct isZero {
  bool operator()(int input) { return input == 0; }
};

struct isNotZero {
  bool operator()(int input) { return input != 0; }
};

struct isFour {
  bool operator()(int input) { return input == 4; }
};

template <typename Pred>
void moveElementsToEndWithPartition(std::vector<int>& v, Pred pred) {
  auto begin = std::begin(v);
  auto end = std::end(v);

  std::advance(end, -1);

  while (begin != end) {
    if (pred(*begin)) {
      pn::algo::swap(*begin, *end);
      end--;
      continue;
    }
    begin++;
  }
}

int main() {
  std::vector<int> v{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 5, 6, 7};
  moveElementsToEnd(v, 0);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));

  std::vector<int> v1{0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 4, 5, 6, 7};
  moveElementsToEndWithPartition(v1, isZero());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));
  moveElementsToEndWithPartition(v1, isFour());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));

  std::partition(std::begin(v1), std::end(v1), isNotZero());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));

  return 0;
}
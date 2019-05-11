// Problem : Is to merge two already sorted ranges into one such that :
// 1. The first vector is sorted and 0 elements are replaced by the actual
// elements Input :: 2 vectors ( alredy sorted, first with zeros of count of
// second vector ) Output :: 2 vectors merged in first and is in order

// Algo: 1. move all zeros to end.
// 2. Replace 0's with INT_MAX
// 3. Merge both lists

#include <limits.h>
#include <vector>
#include "algorithm.h"
#include "functors.h"
#include "merge.h"
#include "swap.h"
#include "utils.h"

struct isZero {
  bool operator()(int input) { return 0 == input; }
};

template <typename Iter, typename Pred>
void moveToEndIf(Iter begin, Iter end, Pred pred) {
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

void mergeRangeAndKeepTheOrderInAsceding(std::vector<int>& v1,
                                         std::vector<int>& v2) {
  pn::algo::mergeRangeAndKeepTheOrder(v1.begin(), v1.end(), v2.begin(),
                                      v2.end(), std::less<>(),
                                      std::greater<>());
}

int main() {
  std::vector<int> v1{1, 0, 3, 0, 5, 0, 7};
  std::vector<int> v2{2, 4, 6};

  moveToEndIf(v1.begin(), v1.end(), isZero());
  pn::algo::replace(v1.begin(), v1.end(), 0, INT_MAX);
  mergeRangeAndKeepTheOrderInAsceding(v1, v2);
  pn::utils::print(std::begin(v1), std::end(v1));
}
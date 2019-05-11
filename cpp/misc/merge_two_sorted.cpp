// Problem : Is to merge two already sorted ranges into one such that :
// 1. The first vector has lower range and second has the upper range
// Input :: 2 vectors ( alredy sorted )
// Output :: 2 vectors merged with first vector with lower range and second
// vector with upper range

// Algo: Compare first element of first range with second and swap if larger
// After swap, emplace the element in second range such that order is not
// broken.

#include <vector>
#include "functors.h"
#include "merge.h"
#include "reverse.h"
#include "swap.h"
#include "utils.h"

void mergeRangeAndKeepTheOrderInAsceding(std::vector<int>& v1,
                                         std::vector<int>& v2) {
  pn::algo::mergeRangeAndKeepTheOrder(v1.begin(), v1.end(), v2.begin(),
                                      v2.end(), std::less<>(),
                                      std::greater<>());
}

void mergeRangeAndKeepTheOrderInDescending(std::vector<int>& v1,
                                           std::vector<int>& v2) {
  pn::algo::reverse(v1.begin(), v1.end());
  pn::algo::reverse(v2.begin(), v2.end());
  pn::algo::mergeRangeAndKeepTheOrder(v1.begin(), v1.end(), v2.begin(),
                                      v2.end(), std::greater<>(),
                                      std::less<>());
}

int main() {
  std::vector<int> v1{0, 2, 4, 6, 8, 10, 12, 14};
  std::vector<int> v2{0, 1, 3, 5, 7, 9, 11, 13};
  // std::vector<int> v2{0, 2, 4, 6, 8, 10, 12, 14};

  mergeRangeAndKeepTheOrderInAsceding(v1, v2);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));
  pn::utils::print<std::vector<int>::iterator>(std::begin(v2), std::end(v2));

  mergeRangeAndKeepTheOrderInDescending(v1, v2);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));
  pn::utils::print<std::vector<int>::iterator>(std::begin(v2), std::end(v2));
}
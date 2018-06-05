// Problem : Is to merge two already sorted ranges into one such that :
// 1. The first vector has lower range and second has the upper range
// Input :: 2 vectors ( alredy sorted )
// Output :: 2 vectors merged with first vector with lower range and second
// vector with upper range

// Algo: Compare first element of first range with second and swap if larger
// After swap, emplace the element in second range such that order is not
// broken.

#include <vector>
#include "swap.h"
#include "utils.h"

void mergeRangeAndKeepTheOrder(std::vector<int>& v1, std::vector<int>& v2) {
  auto b1 = v1.begin();
  auto e1 = v1.end();
  auto e2 = v2.end();

  while (b1 != e1) {
    auto b2 = v2.begin();
    if (*b2 < *b1) {
      pn::algo::swap(*b1, *b2);
      while ((b2 + 1) != e2) {
        if (*b2 > *(b2 + 1)) {
          pn::algo::swap(*b2, *(b2 + 1));
          b2++;
        } else {
          break;
        }
      }
    }
    b1++;
  }
}

int main() {
  std::vector<int> v1{0, 1, 3, 5, 7, 9, 11, 13};
  std::vector<int> v2{0, 2, 4, 6, 8, 10, 12, 14};

  mergeRangeAndKeepTheOrder(v1, v2);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));
  pn::utils::print<std::vector<int>::iterator>(std::begin(v2), std::end(v2));
}
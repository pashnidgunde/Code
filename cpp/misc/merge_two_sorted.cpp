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
#include "swap.h"
#include "utils.h"

template <typename Iter>
void mergeRangeAndKeepTheOrder(Iter begin1, Iter end1, Iter begin2, Iter end2) {
  while (begin1 != end1) {
    auto begin2Temp = begin2;
    if (*begin2Temp < *begin1) {
      pn::algo::swap(*begin1, *begin2);
      while ((begin2Temp + 1) != end2) {
        if (*begin2Temp > *(begin2Temp + 1)) {
          pn::algo::swap(*begin2Temp, *(begin2Temp + 1));
          std::advance(begin2Temp, 1);
        } else {
          break;
        }
      }
    }
    std::advance(begin1, 1);
  }
}

void mergeRangeAndKeepTheOrder(std::vector<int>& v1, std::vector<int>& v2) {
  mergeRangeAndKeepTheOrder(v1.begin(), v1.end(), v2.begin(), v2.end());
}

int main() {
  std::vector<int> v1{0, 1, 3, 5, 7, 9, 11, 13};
  std::vector<int> v2{0, 2, 4, 6, 8, 10, 12, 14};

  mergeRangeAndKeepTheOrder(v1, v2);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));
  pn::utils::print<std::vector<int>::iterator>(std::begin(v2), std::end(v2));
}
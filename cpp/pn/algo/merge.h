#pragma once

#include <vector>
#include "swap.h"

namespace pn {
namespace algo {
template <typename Iter, typename Comparator1, typename Comparator2>
void mergeRangeAndKeepTheOrder(Iter begin1, Iter end1, Iter begin2, Iter end2,
                               Comparator1 comparator1,
                               Comparator2 comparator2) {
  while (begin1 != end1) {
    auto begin2Temp = begin2;
    if (comparator1(*begin2Temp, *begin1)) {
      pn::algo::swap(*begin1, *begin2);
      while ((begin2Temp + 1) != end2) {
        if (comparator2(*begin2Temp, *(begin2Temp + 1))) {
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

}  // namespace algo
}  // namespace pn

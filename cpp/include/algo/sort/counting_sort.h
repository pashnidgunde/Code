#pragma once

#include <map>

namespace pn {
namespace algo {
template <typename Iter, typename Op>
void countingSort(Iter begin, Iter end, Op op) {
  // can't be unordered because we need the order
  // either aschending or descending

  Iter beginOrig = begin;
  std::map<int, int> countOfElements;
  while (begin < end) {
    ++countOfElements[*begin];
    std::advance(begin, 1);
  }

  for (const auto& elem : countOfElements) {
    for (auto i = elem.second; i > 0; --i) {
      *beginOrig = elem.first;
      std::advance(beginOrig, 1);
    }
  }
}
}  // namespace algo
}  // namespace pn
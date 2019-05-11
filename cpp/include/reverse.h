#pragma once
#include "swap.h"

namespace pn {
namespace algo {
template <typename Iter>
void reverse(Iter begin, Iter end) {
  std::advance(end, -1);
  while (begin <= end) {
    pn::algo::swap(*begin, *end);
    std::advance(begin, 1);
    std::advance(end, -1);
  }
}

}  // namespace algo
}  // namespace pn

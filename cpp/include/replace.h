#pragma once

namespace pn {
namespace algo {
template <typename Iter, typename T>
void replace(Iter begin, Iter end, T oldValue, T newValue) {
  while (begin != end) {
    if (*begin == oldValue) {
      *begin = newValue;
    }
    std::advance(begin, 1);
  }
}
}  // namespace algo
}  // namespace pn

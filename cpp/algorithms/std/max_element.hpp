#ifndef max_element_hpp
#define max_element_hpp

namespace pn {
namespace algo {
template <class Iter>
// auto max_element(Iter begin, Iter end) -> decltype(*Iter) {
auto max_element(Iter begin, Iter end) {
  auto max = *begin;
  begin++;
  while (begin != end) {
    if (*begin > max) {
      max = *begin;
    }
    begin++;
  }
  return max;
}
}
}

#endif

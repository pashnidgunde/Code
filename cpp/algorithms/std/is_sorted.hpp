
#ifndef is_sorted_hpp
#define is_sorted_hpp

namespace pn {
namespace algo {
template <typename Iter, typename Op>
// auto max_element(Iter begin, Iter end) -> decltype(*Iter) {
bool is_sorted(Iter begin, Iter end, Op op) {

  while (begin != end && begin + 1 != end && op(*begin, *(begin + 1)))
    begin++;
  return (begin + 1 == end);
}
}
}
#endif

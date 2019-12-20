#include <algorithm>
#include "functors.h"

namespace pn {
namespace algo {
// Accepts range and operator and works with forward iterators only
template <typename Iter, typename Op>
static void bubbleSort(Iter begin, Iter end, Op op) {
  // TO DO
  for (; begin != end; std::advance(begin, 1)) {
    for (Iter innerIter = begin; innerIter != end; std::advance(innerIter, 1)) {
      if (op(*innerIter, *begin)) {
        // TODO
        std::swap(*innerIter, *begin);
      }
    }
  }
}
}  // namespace algo
}  // namespace pn

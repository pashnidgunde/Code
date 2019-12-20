#pragma once
#include <iostream>

namespace pn {
namespace utils {
template <typename Iter>
static void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << " " << *begin << " ";
    begin++;
  }

  std::cout << std::endl;
}
}  // namespace utils
}  // namespace pn

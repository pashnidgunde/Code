#pragma once
#include <iostream>

namespace pn {
namespace utils {
template <typename Iter> static void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << " " << *begin << " ";
    begin++;
  }

  std::cout << std::endl;
}

template <template <typename, typename...> class ContainerType,
          typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...> &c) {
  for (const auto &v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}
}
}

#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> {
  using type = T;
};

template <typename T>
struct enable_if<false, T> {};

int main() {
  struct X {
    enum { value1 = true, value2 = false };
  };

  enable_if<X::value1, int>::type x = 20;
  std::cout << x << std::endl;

  //   enable_if<X::value2, int>::type x1 = 30;
  //   std::cout << x1 << std::endl;
  return 0;
}

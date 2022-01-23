#include <iostream>
#include <type_traits>

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };

int main() {
  std::cout << std::is_same<int, int>::value << "\n";
  std::cout << std::is_same<int, remove_const<const int>::type>::value << "\n";

  return 0;
}
#include <iostream>
#include <type_traits>

// possible implementations
// template <typename T> struct remove_reference { using type = T; };
// template <typename T> struct remove_reference<T &> { using type = T; };
// template <typename T> struct remove_reference<T &&> {
//  using type = T;
//}

template <typename T, typename U> void print_is_same() {
  std::cout << std::is_same<T, U>::value << "\n";
}

int main() {
  print_is_same<int, int>();    // 1
  print_is_same<int, int &>();  // 0
  print_is_same<int, int &&>(); // 0

  print_is_same<int, int>();                                 // 1
  print_is_same<int, std::remove_reference<int &>::type>();  // 1
  print_is_same<int, std::remove_reference<int &&>::type>(); // 1

  return 0;
}
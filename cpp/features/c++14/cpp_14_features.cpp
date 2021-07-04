#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// https://www.youtube.com/watch?v=WZYKzCsACiw&t=185s

namespace cpp_14_feature {
namespace return_type_deduction_by_auto {
// function return type deduction
// allows use of auto in return type

auto func() {
  return 0;
}
static_assert(std::is_same<int, decltype(func())>::value, "Types are not same");

auto func1() {
  return "hello";
}

static_assert(std::is_same<const char*, decltype(func1())>::value,
              "Types are not same");

template <typename T>
class SomeWrapper {
  std::vector<const T*> my_vec;
  // cpp98
  typename std::vector<const T*>::iterator get_begin_cpp98() {
    return my_vec.begin();
  }

  // cpp11
  auto get_begin_cpp11() -> decltype(std::begin(my_vec)) {
    return my_vec.begin();
  }

  // cpp14
  auto get_begin_cpp14() { return my_vec.begin(); }

  // cpp 11
  template <typename T1, typename T2, typename T3>
  auto getComplexReturnType_cpp11(T1 a, T2 b, T3 c) -> decltype(a * b * c) {
    return a * b * c;
  }

  template <typename T1, typename T2, typename T3>
  auto getComplexReturnType_cpp14(T1 a, T2 b, T3 c) {
    return a * b * c;
  };
};
}  // namespace return_type_deduction_by_auto

int main() {
  return 0;
}
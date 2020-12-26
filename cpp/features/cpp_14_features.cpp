#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// Youtube video
// Dive into C++14 - [1] - Introduction to C++14 core language features

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

auto func2() {
  std::string x = "hello";
  return x;
}

static_assert(std::is_same<const char*, decltype(func1())>::value,
              "Types are not same");

static_assert(std::is_same<std::string, decltype(func2())>::value,
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
  }
};
}  // namespace return_type_deduction_by_auto
}  // namespace cpp_14_feature

namespace cpp_14_feature {
namespace decltype_auto {
// auto will always deduce non-reference type
// auto&& will always deduce a reference type
// decltype(auto) deduces a non-reference or reference based on nature of
// expression

auto func3() {
  static std::string test("XX");
  auto& result(test);
  return result;
}

static_assert(std::is_same<std::string, decltype(func3())>::value,
              "auto always returns non-reference");

decltype(auto) func4() {
  static std::string test("XX");
  auto& result(test);
  return result;
}

static_assert(std::is_same<std::string&, decltype(func4())>::value,
              "with decltype(auto) it must return reference type");

}  // namespace decltype_auto
}  // namespace cpp_14_feature

namespace cpp_14_feature {
namespace relaxed_const_expr {
// constexpr can evaluate certain computations if it has loops and ifs
// as long everything can be computed at compile time
constexpr int computeSomething(int x) {
  int y = 0;
  for (int i = 0; i < x; ++i) {
    y = y + i;
  }
  if (y % 20 == 0)
    y = y % 20;

  return y;
}
static_assert(computeSomething(0) == 0,
              "computeSomething must compute this at compile time");

template <int X>
struct Y {};

Y<computeSomething(10)> instance_y_where_x_is_computed_at_compile_time;

}  // namespace relaxed_const_expr
}  // namespace cpp_14_feature

namespace cpp_14_feature {
namespace variable_templates {
// c++14 allows creation of templated variables
// variable templates can be specialized

template <typename T>
// line below doesnt compile :
// error: narrowing conversion of ‘3.1415151515000002e+0’ from ‘double’ to ‘int’
// T pi{3.1415151515};
double pi{3.122222};

void test0() {
  auto int_pi(pi<int>);
  auto float_pi(pi<float>);
  auto double_pi(pi<double>);
  std::cout << int_pi << " , " << float_pi << " , " << double_pi << std::endl;
}

// specialization
template <typename Z>
int TypeID;

template <>
constexpr int TypeID<int>{0};

template <>
constexpr int TypeID<float>{1};

template <>
constexpr int TypeID<double>{2};

void test1() {
  static_assert(TypeID<int> == 0, "");
  static_assert(TypeID<float> == 1, "");
  static_assert(TypeID<double> == 2, "");
}

}  // namespace variable_templates
}  // namespace cpp_14_feature

namespace cpp_14_feature {
namespace generic_lambdas_with_auto {
// lambda function parameters can be auto and return types are determined by
// input params
auto lambda1 = [](auto x) { return x * 2; };
static_assert(std::is_same<int, decltype(lambda1(2))>(),
              "as return is int, auto returns int");
static_assert(std::is_same<float, decltype(lambda1(2.f))>(),
              "as return is float, auto returns float");
static_assert(std::is_same<double, decltype(lambda1(2.0))>::value,
              "as return is double, auto returns double");

void test() {
  std::cout << lambda1(2.334) << std::endl;
}

// compiler generated code below for lambda above
// auto l2(auto x, auto y) {
//  return x * y;
//}

// struct CompilerGeneratedLambda {
//  template <typename X, typename Y>
//  auto operator(){X x, Y y} {
//    return x * y;
//  }
}  // namespace generic_lambdas_with_auto

}  // namespace cpp_14_feature
}  // namespace cpp_14_feature

int main() {
  std::cout << cpp_14_feature::relaxed_const_expr::computeSomething(0);
  cpp_14_feature::generic_lambdas_with_auto::test();
  return 0;
}
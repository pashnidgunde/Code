#include <iostream>
#include <utility>

// struct A {
//   A(int& rhs) { std::cout << "Copy Constructor : " << rhs << std::endl; }
//   A(int&& rhs) { std::cout << "Move constructor : " << rhs << std::endl; }
// };

// // Note this always forwards as reference
// struct B {
//   B(int a) : _1(std::forward<int>(a)) {}

//   A _1;
// };

// struct B1 {
//   template <typename T1, typename T2>
//   B1(T1&& p1, T1&& p2) : _1(std::forward<T1>(p1)), _2(std::forward<T1>(p2))
//   {}

//   A _1, _2;
// };

struct Test {
  template <typename T, typename T1>
  Test(T&& x, T&& y) : _x(x), _y(y) {}

  int _x;
  int _y;
};

int main() {
  // // Copy and move constructor demo
  // A a(10);
  // int a1 = 20;
  // A a2(a1);

  // // std::forward with rvalue and lvalue that alwyas forwards
  // B b(10);
  // B b1(a1);

  // B1 bb(10, 20);
  // B1 bb1(a1, 20);

  Test x(10, 10);

  return 0;
}
#include <iostream>

namespace cpp_11_feature {
namespace std_forward {
// forwarding to functions
void func(int& n) {
  std::cout << "L value overload : " << n << std::endl;
}

void func(int&& n) {
  std::cout << "R value overload : " << n << std::endl;
}

template <typename T>
void wrapper(T&& param) {
  func(std::forward<T>(param));
}
}  // namespace std_forward
}  // namespace cpp_11_feature

int main() {
  wrapper(0);
  int x = 0;
  wrapper(x);
  return 0;
}
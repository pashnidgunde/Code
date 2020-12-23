#include <functional>
#include <iostream>

void f(int &n1, int &n2, const int &n3) {
  std::cout << "In function : " << n1 << ' ' << n2 << ' ' << n3 << '\n';
  ++n1; // increments the copy of n1 stored in the function object
  ++n2; // increments the main()'s y
  // n3++; compile error
}

int main() {
  int x = 0, y = 0, z = 0;

  // when you bind , no need to provide params to std::func
  std::function<void()> func_with_bind =
      std::bind(f, x, std::ref(y), std::cref(z));
  x++;
  y++;
  z++;

  std::cout << "Before : " << x << ' ' << y << ' ' << z << '\n';
  func_with_bind();

  std::cout << "After : " << x << ' ' << y << ' ' << z << '\n';

  return 0;
}
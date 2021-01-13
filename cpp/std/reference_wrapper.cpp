#include <functional>
#include <iostream>
#include <vector>

// https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

void func(int &x, int &y, int &z) {
  x++;
  y++;
  z++;

  std::cout << "X : " << x << ", Y : " << y << ", Z : " << z << '\n'
}

int main() {
  std::vector<int> v{1, 2, 3, 4};

  // This line wont compile because containers need copyable objects
  // std::vector<int &> v2(v.begin(), v.end());
  // std::reference_wrapper is a class template that wraps a reference in a
  // copyable, assignable object.
  std::vector<std::reference_wrapper<int>> v1(v.begin(), v.end());

  for (int &elem : v) {
    elem = elem * 2;
  }

  for (int elem : v1) {
    std::cout << elem << " , ";
  }
}

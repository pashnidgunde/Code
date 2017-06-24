#include <iostream>
#include <vector>

template <class Func> void check(Func f, std::vector<int> &v) {
  for (auto i : v) {
    if (f(i)) {
      std::cout << i << std::endl;
    }
  }
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5};

  // First function that checks if element is greater than 3 and prints
  auto function1 = [](int x) { return x > 3; };
  auto function2 = [](int x) { return x >= 1; };
  auto function3 = [](int x) { return x < 2; };
  auto function4 = [](int x) { return !x; };
  auto function5 = [](int x) { return x || 3; };
  auto function6 = [](int x) { return x == 3; };

  check(function1, v);
  check(function2, v);
  check(function3, v);
  check(function4, v);
  check(function5, v);
  check(function6, v);
}
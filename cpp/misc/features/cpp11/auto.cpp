#include <iostream>

int main() {
  auto i = 0;   // int
  auto j = 5.0; // double

  std::vector<int> vec { 1, 2, 2, 3, 0 }

  // Note that the element is by ref making values to increment
  for (auto &element : vec) {
    element++;
  }

  return 0;
}

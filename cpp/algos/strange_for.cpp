#include <iostream>
#include <vector>

int main() {
  std::vector<int> v{1};

  std::cout << "Size:: " << v.size();

  for (unsigned int i = 0; i + 2 <= v.size(); i++) {
    std::cout << "Hello";
  }

  return 0;
}
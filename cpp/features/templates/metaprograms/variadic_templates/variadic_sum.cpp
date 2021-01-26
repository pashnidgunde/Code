#include <iostream>

template <typename T> T sum(T last) { return last; }

template <typename T, typename... Args> // template parameter pack
T sum(T first, Args... rest)            // function parameter pack
{
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return first + sum(rest...);
  // for (1,2,3,4,5)
  // return 1 + sum(2,3,4,5)
  // return 1 + 2 + sum(3,4,5)
  // return 1 + 2 + 3 + sum(4,5)
  // return 1 + 2 + 3 + 4 + sum(5)
  // return 1 + 2 + 3 + 4 + 5
}

int main() {
  std::cout << sum(1, 2, 3, 4, 5) << std::endl;
  std::cout << sum(std::string("A"), std::string("B"), std::string("C"),
                   std::string("D"), std::string("E"))
            << std::endl;
  return 0;
}
#include <iostream>
#include <sstream>

template <typename T> std::string to_string(T args) {
  std::stringstream s;
  s << args;
  return s.str();
}

void toString() { return; }

template <typename T, typename... Params>
void toString(const T &param, const Params... params) {
  std::cout << param;
  toString(params...);
}

template <typename T, typename... Rest>
std::string to_string(T first, const Rest &... rest) {
  std::stringstream s;
  s << first;
  s << to_string(rest...);
  return s.str();
}

int sum() { return 0; }

template <typename First, typename... Rest>
int sum(const First &first, const Rest &... rest) {
  return first + sum(rest...);
}

int main() {
  std::cout << to_string(10) << std::endl;
  toString(1, 2, 2, 3, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6);
  std::cout << to_string(1, "Hello", "5.5"
                                     "Done Done Done");

  std::cout << sum(1, 2, 2, 3, 4, 4, 5, 5, 5, 5, 55);
}
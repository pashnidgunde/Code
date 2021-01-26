#include <cassert>
#include <iostream>

bool compare() { return true; }

template <typename T> bool compare(T arg) { return false; }

template <typename T, typename... Args>
bool compare(const T &a, const T &b, Args... rest) {
  return a == b && compare(rest...);
}

int main() {
  assert(true == compare(1, 1, 2, 2, 3, 3));
  assert(true == compare(1, 1, 2, 2, 3, 4));
  assert(false == compare(1, 1, 2, 2, 3, 4, 5));
  assert(true == compare(std::string("a"), std::string("a")));
  return 0;
}
#include <iostream>

class NonCopyable {
public:
  NonCopyable() = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
};

class NonCopyableX : public NonCopyable {
public:
  NonCopyableX() = default;
};

int main() {
  // Compilation error for below
  NonCopyable lhs;
  NonCopyable rhs(rhs);
  lhs = rhs;

  // Compilation Error for derived class
  NonCopyableX x;
  NonCopyableX x1(x);
  NonCopyableX x2 = x;

  return 0;
}
#include <iostream>

class NonCopyable {
 public:
  NonCopyable(int data) : data_(data) {}
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable &operator=(const NonCopyable &) = delete;
  NonCopyable(NonCopyable &&other) : data_(std::move(other.data_)) {}

 private:
  int data_;

 public:
  int getData() { return data_; }
};

class NonCopyableX : public NonCopyable {
 public:
  NonCopyableX(int data) : NonCopyable(data) {}
  NonCopyableX() = delete;
};

int main() {
  /*
  // Compilation error for below
  NonCopyable lhs;
  NonCopyable rhs(rhs);
  lhs = rhs;

  // Compilation Error for derived class
  NonCopyableX x;
  NonCopyableX x1(x);
  NonCopyableX x2 = x;
  */

  /* This works after adding a move constructor, but it doesn't move */
  NonCopyable a(100);
  NonCopyable a1(std::move(a));
  NonCopyable a2 = std::move(a1);
  std::cout << a.getData() << a1.getData() << a2.getData();

  // NonCopyableX x(10);
  // NonCopyableX x1(NonCopyableX(x));
  // std::cout << x1.getData();
  // std::cout << x.getData();
  return 0;
}
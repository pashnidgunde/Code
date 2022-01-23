#include <iostream>

// X * 2 is possible but 2 * X is not possible

class X {
public:
  X(int a) { _a = a; }

  /*
  X operator *(X& aa)
  {
      return _a * aa._a;
  }
  */

  friend X operator*(X a, X b);
  friend std::ostream &operator<<(std::ostream &os, const X &x);

  /*
  int operator()()
  {
      return _a;
  }
  */

private:
  int _a;
};

X operator*(X a, X b) { return a._a * b._a; }

std::ostream &operator<<(std::ostream &os, const X &x) {
  os << x._a;
  return os;
}

int main() {
  X a1(10);

  // This is possible using member operator and global operator
  // but not both as its ambiguous to compiler
  X a2 = a1 * a1;

  // This is not supported by member operator
  // This is possible only if you have a global friend operator
  X a3 = a1 * 20;

  // overloaded global << operator
  std::cout << a1 << a2 << a3 << std::endl;

  //    int x =  a1;

  return 0;
}

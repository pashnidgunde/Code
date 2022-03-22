#include <iostream>

class X {
public:
  virtual void print() { std::cout << "X"; }
};

class Y : public X {
public:
  void print() { std::cout << "Y"; }
};

int main() {
  X x;
  Y y;

  std::cout << sizeof(x) << " " << sizeof(y) << " " << sizeof(X) << " "
            << sizeof(Y);
  y.print(); // resolved statically

  x = y;
  x.print(); // resolved statically
}

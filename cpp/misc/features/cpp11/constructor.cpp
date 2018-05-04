#include <iostream>

class X {

public:
  ~X() { std::cout << "Destructor"; }
};

int main() {
  X a;
  // a.X();   // You can't explicitly call constructor but not Destructor
  a.~X();
  return 0;
}

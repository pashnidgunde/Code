// Example of order of construction.
// Here B is derived from A and composes C

#include <iostream>

class A {
public:
  A() { std::cout << "A constructor" << std::endl; }
};

class C {
public:
  C() { std::cout << "C Constructor" << std::endl; }
};

class B : public A {
public:
  B() { std::cout << "B Constructor" << std::endl; }

private:
  C c;
};

int main() {
  B b;
  return 0;
}

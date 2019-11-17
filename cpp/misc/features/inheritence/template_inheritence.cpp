#include <iostream>

class X {
public:
  X(int a) { std::cout << a << std::endl; }
};

class Y {
public:
  // Y(auto x) error: 'auto' not allowed in function prototype
  Y(float x) { std::cout << "In Y" << x << std::endl; }
};

template <class T> class A : public T {
public:
  A(int x) : T(x) {}
};

template <class Z> class B : public A<Z> {
public:
  B(float x) : A<Z>((int)x) {}
};

int main() {
  A<X> z(10);
  B<Y> xx(200.00);
  return 0;
}

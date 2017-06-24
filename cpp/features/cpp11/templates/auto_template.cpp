// Template that accepts auto

#include <iostream>
#include <typeinfo>

template <class T> void fun(T a) {
  std::cout << typeid(a).name() << " " << a << std::endl;
}

int main() {
  auto t = 10.40;
  fun(t);
  return 0;
}

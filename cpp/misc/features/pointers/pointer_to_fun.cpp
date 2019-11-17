#include <iostream>

int function1(int x) {
  std::cout << "Function1 "
            << " :: " << x << std::endl;
  return 0;
}

class X {
public:
  void public_function() { std::cout << "Public Function" << std::endl; }
};

int main() {
  // return_type (*ptr_name) (params,...)
  int (*ptr_fun)(int) = &function1;
  // No dereferencing when you call
  ptr_fun(10);

  // return_type(class::*ptr_name)(params) = &class::member function name
  // without ()
  void (X::*ptr_pub_fun)() = &X::public_function;
  X xx;
  (xx.*ptr_pub_fun)();

  return 0;
}

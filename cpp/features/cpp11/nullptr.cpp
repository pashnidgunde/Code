#include <iostream>

void foo(int i) { std::cout << "Foo int" << std::endl; }

void foo(char* ptr) { std::cout << "Foo (char*)" << std::endl; }

int main() {
  // C++ 08
  // foo(NULL);   // is ambiguous

  // C++ 11
  foo(nullptr);  // Not ambiguous
  foo(0);        // Not ambiguous

  return 0;
}
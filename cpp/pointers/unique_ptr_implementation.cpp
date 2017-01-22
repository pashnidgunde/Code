/*
 * unique_ptr_implementation.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <iostream>

template <class T>
class unique_ptr {
 private:
  T *_ptr;

 public:
  unique_ptr(T *ptr) : _ptr(ptr) {}

  ~unique_ptr() { delete _ptr; }

  T *get() { return _ptr; }

  T *operator->() { return _ptr; }

  T &operator*() { return *_ptr; }
};

class X {
 public:
  X() { std::cout << "Constructor"; }
  ~X() { std::cout << "Destructor"; }
  void print() { std::cout << "Hello World"; }
};

int main() {
  unique_ptr<X> x(new X());
  x->print();
  (*x).print();
  return 0;
}

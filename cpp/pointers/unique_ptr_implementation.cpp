/*
 * unique_ptr_implementation.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <cassert>
#include <iostream>

template <class T> class unique_ptr {
private:
  T *_ptr;

public:
  unique_ptr(T *ptr) : _ptr(ptr) {}
  unique_ptr(const unique_ptr<T> &other) = delete;
  unique_ptr(unique_ptr<T> &&other) : _ptr(nullptr) {
    std::swap(_ptr, other.ptr);
  }

  ~unique_ptr() { delete _ptr; }

  T *get() { return _ptr; }

  T *operator->() { return _ptr; }

  T &operator*() { return *_ptr; }

  unique_ptr<T> &operator=(const unique_ptr<T> &other) = delete;
  unique_ptr<T> &operator=(const unique_ptr<T> &&other) {
    if (_ptr) {
      delete _ptr;
      _ptr = nullptr;
    }
    swap(_ptr, other._ptr);
  }
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

  // This should throw an error as copy Constructor is not supported.
  // unique_ptr<X> x1 = x;
  // unique_ptr<X> x2(x);

  unique_ptr<X> x_move_constructed(std::move(x));
  assert(nullptr == x.get());
  assert(nullptr != x_move_constructed.get());
  x_move_constructed->print();

  unique_ptr<X> x_move_assigned = std::move(x_move_constructed);
  assert(nullptr == x_move_constructed.get());
  assert(nullptr != x_move_assigned.get());
  x_move_assigned->print();

  return 0;
}

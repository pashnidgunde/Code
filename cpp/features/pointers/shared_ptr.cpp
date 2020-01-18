/*
 * shared_ptr.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <iostream>

class RefCount {
private:
  int _count;

public:
  RefCount(int count) : _count(count) {}
  void addRef() { _count++; }
  void decRef() { _count--; }
  int getCount() { return _count; }
};

template <class T> class shared_ptr {
private:
  T *_ptr;
  RefCount *rc;

  RefCount *getRC() { return rc; }

public:
  shared_ptr(T *ptr) : _ptr(ptr), rc(new RefCount(0)) { std::cout << "C"; }
  ~shared_ptr() {
    std::cout << "D";
    rc->decRef();
    if (rc->getCount() == 0)
      delete _ptr;
  }

  T *get() { return _ptr; }

  shared_ptr(shared_ptr<T> &other) : _ptr(other.get()), rc(other.getRC()) {
    rc->addRef();
  }

  shared_ptr<T> &operator=(shared_ptr<T> &other) {
    if (other == *this)
      return *this;

    this->_ptr = other.get();
    this->rc = other.getRC();
    this->rc.addRef();

    return *this;
  }
};

class X {
public:
  X() { std::cout << "XC"; }
  ~X() { std::cout << "XD"; }
};

int main() {
  shared_ptr<X> x(new X());
  shared_ptr<X> y = x;
  shared_ptr<X> z = x;
}

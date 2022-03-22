#include <functional>
#include <iostream>
#include <string>

class MyVector {

public:
  MyVector() : size(0), ptr(nullptr) {}
  ~MyVector() { delete[] ptr; }

  // Copy constructor
  MyVector(const MyVector &other) : size(other.size) {
    ptr = new int[size];
    for (int i = 0; i < size; i++) {
      ptr[i] = other.ptr[i];
    }
  }

  // Move constructor
  /* Old style Move constructor but we can use swap */
  // MyVector(MyVector &&other) : size(other.size), ptr(other.ptr) {
  //  other.size = 0;
  //  other.ptr = nullptr;
  //}

  MyVector(MyVector &&other) : size(0), ptr(nullptr) { this->swap(other); }

  // Copy assing operator
  // Old style
  /*
  MyVector &operator=(const MyVector &other) {
    if (&other == this) {
      return *this;
    }
    this->size = other.size;
    this->ptr = new int[this->size];
    for (int i = 0; i < size; i++) {
      ptr[i] = other.ptr[i];
    }
  }

  */

  // Incomplete
  MyVector &operator=(MyVector other) { return *this; }

private:
  int size;
  int *ptr;

  void swap(MyVector &other) {
    std::swap(size, other.size);
    std::swap(ptr, other.ptr);
  }
};

std::string getHello() { return "Hello"; }

int main() {

  int x = 0; // L values x and k
  int y = 100;
  // *************Lvalue reference to x
  int &volatile_lvalue_reference = x;

  volatile_lvalue_reference = 100;         // Possible changing value
  volatile_lvalue_reference = std::ref(y); // Can't reference to R value

  // const lvalue reference pointing to rvalue 0
  const int &const_lvalue_reference = 0;

  // volatile rvalue reference
  int &&volatile_rvalue_reference = 0;

  // const rvalue reference
  const int &&const_rvalue_reference = 0;
  // Rvalue references can't reference to lvalue
  // const int &&const_rvalue_reference_1 = x;

  std::cout << volatile_lvalue_reference << const_lvalue_reference
            << volatile_rvalue_reference << const_rvalue_reference << std::endl;

  std::string s("Prashant");
  std::string s1(s); // Copy constructor

  // Copy constructor Before C++11 , Move constructor after c++11
  std::string s3(getHello());

  return 0;
}

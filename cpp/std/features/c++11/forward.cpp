#include <iostream>

class MyIntVector {

private:
  int *ptr = nullptr;
  int size = 0;

public:
  MyIntVector(const MyIntVector &other) {
    this->realloc(other.size);
    for (int i = 0; i < size; i++) {
      ptr[i] = other.ptr[i];
    }
  }

  MyIntVector(MyIntVector &&other) : ptr(nullptr), size(0) {
    this->release();
    this->size = std::move(other.size);
    this->ptr = std::move(other.ptr);
    other.size = 0;
    other.ptr = nullptr;
  }

  MyIntVector(const size_t size) {
    this->size = size;
    this->alloc(size)
  }

  ~MyIntVector() { release(); }

private:
  void release() {
    if (ptr) {
      delete[] ptr;
      ptr = nullptr;
    }
  }

  void alloc(const size_t &size) {
    this->size = size;
    ptr = new int[size];
  }

  void realloc(const size_t &size) {
    this->release();
    this->alloc(size);
  }
};

void foo(MyIntVector v) {}

template <class T> void relay(const T &type) { foo(type); }

int main() {
  MyIntVector v(10);
  MyIntVector v1(20);
}
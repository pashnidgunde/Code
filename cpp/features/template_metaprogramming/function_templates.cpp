#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

template <typename T>
bool equal(const T& lhs, const T& rhs) {
  std::cout << "Generic == comparison" << std::endl;
  return lhs == rhs;
}

// NOTE :
// Partial specialization can not be applied to functions
// Error : error: non-class, non-variable partial specialization ‘equal<T*>’ is
// not allowed template <typename T>
// bool equal<T*>(const T* lhs, const T* rhs)
// {
//   return *lhs == *rhs;
// }

template <typename T>
bool equal(const T* lhs, const T* rhs) {
  std::cout << "Generic pointer values comparison" << std::endl;
  return *lhs == *rhs;
}

template <>
bool equal(const int* lhs, const int* rhs) {
  std::cout << "Integer pointer comparison" << std::endl;
  return *lhs == *rhs;
}

template <>
bool equal(const double& lhs, const double& rhs) {
  std::cout << "This is double comparison" << std::endl;
  // should use googletest::almost equal
  // or
  // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
  return fabs(lhs - rhs) < std::numeric_limits<double>::epsilon();
}

template <>
bool equal(const float& lhs, const float& rhs) {
  std::cout << "This is float comparison" << std::endl;
  return fabs(lhs - rhs) < std::numeric_limits<float>::epsilon();
}

template <>
bool equal(const char* lhs, const char* rhs) {
  std::cout << "This is char* comparison" << std::endl;
  return strcmp(lhs, rhs) == 0;
}

int main() {
  std::cout << equal(1, 1) << std::endl;
  std::cout << equal(2.0, 2.0) << std::endl;
  std::cout << equal(2.0f, 2.0f) << std::endl;
  std::cout << equal("Hello", "Hello") << std::endl;
  int x = 0;
  int y = 0;
  std::cout << equal(&x, &y) << std::endl;  // This defaults to generic int
                                            // comparison as pointers are const

  const int* p = &x;
  const int* q = &y;
  std::cout << equal(p, q) << std::endl;
  return 0;
}

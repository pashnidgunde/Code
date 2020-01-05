#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// template <typename T>
// bool equal(const T& lhs, const T& rhs) {
//   std::cout << "Generic == comparison" << std::endl;
//   return lhs == rhs;
// }
// NOTE :
// Partial specialization can not be applied to functions
// Error : error: non-class, non-variable partial specialization ‘equal<T*>’ is
// not allowed template <typename T>
// bool equal<T*>(const T* lhs, const T* rhs)
// {
//   return *lhs == *rhs;
// }

template <typename T = int>
struct IsEqual {
  bool operator()(const T& lhs, const T& rhs) { return lhs == rhs; }
};

template <typename T>
struct IsEqual<T*> {
  bool operator()(const T* lhs, const T* rhs) { return *lhs == *rhs; }
};

template <>
struct IsEqual<char*> {
  bool operator()(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs) == 0;
  }
};

int main() {
  //   std::cout << equal(2.0, 2.0) << std::endl;
  //   std::cout << equal(2.0f, 2.0f) << std::endl;
  //   std::cout << equal("Hello", "Hello") << std::endl;
  //   int x = 0;
  //   int y = 0;
  //   std::cout << equal(&x, &y) << std::endl;  // This defaults to generic int
  //                                             // comparison as pointers are
  //                                             const

  //   const int* p = &x;
  //   const int* q = &y;
  //   std::cout << equal(p, q) << std::endl;

  IsEqual<int> X;
  IsEqual<int*> IntPtrCompare;
  IsEqual<char*> StrCompare;
  int x = 10;
  int y = 10;

  std::cout << std::boolalpha << X(10, 10) << std::endl;
  std::cout << std::boolalpha << IntPtrCompare(&x, &y) << std::endl;

  std::string lhs_str = "Hello";
  std::string rhs_string = "Hello";
  std::cout << std::boolalpha << StrCompare(lhs_str.c_str(), rhs_string.c_str())
            << std::endl;

  std::vector<int> v1{1, 2, 3, 4, 4};
  std::vector<int> v2{1, 2, 3, 3, 4};
  std::cout << std::boolalpha
            << std::equal(v1.begin(), v1.end(), v2.begin(), IsEqual<int>())
            << std::endl;

  return 0;
}

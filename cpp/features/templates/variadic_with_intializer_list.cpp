#include <iostream>

// print has lot of compile time recursion, the goal is to avoid compile time
// recursion using initializer_list

void print() {}

template <typename FirstType, typename... RestType>
void print(const FirstType& first, const RestType&... rest) {
  std::cout << first << std::endl;
  print(rest...);
  //{print(2),{3,4,5,"Hello"}}
  //{print(3),{4,5,"Hello"}}
  //{print(4),{5,"Hello"}}
  //{print(5),{"Hello"}}
  //{print("Hello"),}}
  //{print}  // no args
}

template <typename T>
void print_impl(T arg) {
  std::cout << arg << std::endl;
}

template <typename... T>
void print_modified(T... args) {
  // below line causes a compiler warning with clang :
  // print(1, 2, 3, 4, 5.0, "Hello");
  // std::initializer_list<int>{(print_impl(args), 0)...};

  // to tell compiler that you are not interested in return value
  // use (void)

  // comma operator
  // int i = (5, 10); // /* 10 is assigned to i*/

  // f1() is called (evaluated) first followed by f2().
  // The returned value of f2() is assigned to j* /
  // int j = (f1(), f2());

  // similarly, 0 is assigned to list, but print_impl is evaluated first
  //(void) tells that compiler that you are not interested in intializer_list
  // value and compiler optimizes it
  (void)std::initializer_list<int>{(print_impl(args), 0)...};

  // above statement can also be written as:
  (void)std::initializer_list<int>{(std::cout << args << std::endl, 0)...};
}

int f1() {
  std::cout << "F1" << std::endl;
  return 1;
}

int f2() {
  std::cout << "F2" << std::endl;
  return 2;
}

int main() {
  print(1, 2, 3, 4, 5.1, "Hello");
  std::cout << "----------------" << std::endl;
  // clang evaluates F1 and then f2
  // g++ evaluates F2 and then F1
  print_modified(1, 2, 3, 4, 5.1, "Hello", f1(), f2());
  return 0;
}
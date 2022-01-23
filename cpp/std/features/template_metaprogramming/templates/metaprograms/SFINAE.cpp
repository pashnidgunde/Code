#include <iostream>
#include <string>

template <typename T> void print(T param) {
  std::cout << param.value << std::endl;
}

template <> void print(double x) {
  std::cout << "Printing double : " << x << std::endl;
}

struct IntType {
  int value = 0;
};

struct StringType {
  std::string value = "default_value";
};

int main() {
  IntType int_type;
  print(int_type);

  StringType string_type;
  print(string_type);

  // =>> SFINAE as double does not have value param
  print(10.00);

  return 0;
}
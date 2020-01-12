#include <iostream>
#include <memory>

int fibonacci() {
  static int i = 0;
  static int j = 1;
  if (i == 0)
    return 0;
  if (j == 1)
    return 1;
  temp = i + j;
  i = j;
  j = temp;
  return temp;
}

int main() {

  int i = 100;
  // note () not required for lambdas not accepting any params
  auto lambda_func = [i] { std::cout << "captured i = " << i << std::endl; };
  lambda_func();

  // stateful lamdas
  // note : x is not declared and is used directly
  // note use of mutable as state needs to be chagned
  // also parenthesis required when using stateful lambdas
  auto stateful_lambda = [x = 0]() mutable {
    std::cout << "Lambda called for : " << ++x << " times" << std::endl;
  };

  stateful_lambda();
  stateful_lambda();
  stateful_lambda();

  // Non copyable stateful lambdas
  // not mutiple catpures
  auto non_copyable = [y = 0, ptr = std::make_unique<int>(10)]() {
    std::cout << "Y : " << y << " and , *ptr =" << *ptr << std::endl;
  };
  // auto copy = non_coyable;--> compilation error

  // stateful lambda that calculates fibonacci sequence

  return 0;
}

#include <iostream>
#include <memory>

// Stateful lambda is nothing but somthing that is captured in [] with values
// are treated like static variables. As static variables maintain their state,
// stateful lambdas can maintain state of their variables

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
  auto non_copyable = [ y = 0, ptr = std::make_unique<int>(10) ]() {
    std::cout << "Y : " << y << " and , *ptr =" << *ptr << std::endl;
  };
  // auto copy = non_coyable;--> compilation error

  // stateful lambda that calculates fibonacci sequence

  auto fibonacci_per_call = [ first = 0, second = 1 ]() mutable->int {
    // traditional approach
    // auto temp = first + second;
    // first = second;
    // second = temp;
    // return temp;

    // with std::exchange
    first = std::exchange(second, first + second);
    return first;
  };

  std::cout << fibonacci_per_call() << std::endl;
  std::cout << fibonacci_per_call() << std::endl;
  std::cout << fibonacci_per_call() << std::endl;
  std::cout << fibonacci_per_call() << std::endl;
  std::cout << fibonacci_per_call() << std::endl;
  std::cout << fibonacci_per_call() << std::endl;

  return 0;
}

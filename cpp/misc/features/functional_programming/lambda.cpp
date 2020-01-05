#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  auto hello_lambda = []() { std::cout << "Hello from lambda" << std::endl; };
  hello_lambda();

  auto lambda_with_args = [](int x) {
    std::cout << "Printing : " << x << std::endl;
  };
  lambda_with_args(10);

  int x = 10;
  auto lambda_with_capture_by_val_only_x = [x]() {
    std::cout << "Lambda with value " << x << std::endl;
  };
  lambda_with_capture_by_val_only_x();

  int y = 20;
  auto lambda_capture_all_locals_by_value = [=]() {
    std::cout << "Lambda with all locals captured. x= " << x << ", y = " << y
              << std::endl;
  };
  lambda_capture_all_locals_by_value();

  auto lambda_capture_all_locals_by_value_and_ref = [x, &y]() {
    y++;
    std::cout << "Lambda with all locals captured. x= " << x << ", y = " << y
              << std::endl;
  };
  lambda_capture_all_locals_by_value_and_ref();

  auto lambda_capture_all_locals_by_ref = [&]() {
    x++;
    y++;
    std::cout << "Lambda with all locals captured. x= " << x << ", y = " << y
              << std::endl;
  };
  lambda_capture_all_locals_by_ref();

  std::vector<int> v{1, 2, 3, 4, 5};
  auto lambda_with_condition = [](int x) { return x > 3; };
  auto it = std::find_if(std::cbegin(v), std::cend(v), lambda_with_condition);
  std::cout << ((it != std::cend(v)) ? "found" : " not found") << std::endl;

  return 0;
}
#include <algorithm>
#include <iostream>

int main() {
  // auto <name> [] (params) { } ;
  // Note semicolon in the end
  auto hello = []() { std::cout << "Hello" << std::endl; };
  hello();

  // Lambda that accepts the parameters
  auto product = [](int x, int y) { std::cout << x * y << std::endl; };
  product(5, 5);

  // Lambda that captures
  auto i = 10;
  auto sum_that_captures_i = [i](int x) { std::cout << i + x << std::endl; };
  sum_that_captures_i(20);

  // Sum that returns , note -> int
  auto sum_that_returns = [i](int x) -> int { return i + x; };
  std::cout << sum_that_returns(20) << std::endl;

  // capturing  params as ref
  auto sum_with_ref_capture = [&i]() -> int { return i++; };
  sum_with_ref_capture();
  std::cout << i << std::endl;
  int x = 30;
  auto sum = [](int &x) { x++; };
  sum(x);
  std::cout << x << std::endl;

  // passing all parameters to lambda functions with value =
  int j = 20;
  auto sum_all_by_value = [=]() -> int { return i + x + j; };
  std::cout << sum_all_by_value() << std::endl;

  // passing all parameters to lambda functions with value & ( note [&] )
  auto sum_all_by_ref = [&]() -> int {
    i++;
    j++;
    x++;
    return i + x + j;
  };
  std::cout << i << " " << j << " " << x << " " << sum_all_by_ref()
            << std::endl;

  // Lambda with for_each
  // note that below total is captured by ref
  std::vector<int> v{1, 2, 3, 4, 5};
  auto total = 0;
  std::for_each(std::begin(v), std::end(v), [&total](int x) { total += x; });
  std::cout << total << std::endl;

  return 0;
}

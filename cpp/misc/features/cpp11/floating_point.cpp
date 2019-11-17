#include <iomanip>
#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
//#include <cassert>

int main() {
  // This is float
  constexpr auto f = 0.1f;
  constexpr auto f1 = 0.2f;
  constexpr auto f3 = 0.3f;
  constexpr auto f4 = f + f1;

  std::cout << std::setw(20) << std::setprecision(20) << f << std::endl;
  std::cout << std::setw(20) << std::setprecision(20) << f1 << std::endl;
  std::cout << std::setw(20) << std::setprecision(20) << f3 << std::endl;
  std::cout << std::setw(20) << std::setprecision(20) << f4 << std::endl;

  static_assert(f3 == f4, "Two floating point numbers are not same");

  // This is double
  constexpr auto d = 0.1;
  constexpr auto d1 = 0.2;
  constexpr auto d3 = 0.3;
  constexpr auto d4 = f + f1;

  std::cout << std::setw(40) << std::setprecision(40) << d << std::endl;
  std::cout << std::setw(40) << std::setprecision(40) << d1 << std::endl;
  std::cout << std::setw(40) << std::setprecision(40) << d3 << std::endl;
  std::cout << std::setw(40) << std::setprecision(40) << d4 << std::endl;

  static_assert(d3 == d4, "Two double precision numbers are not same");

  return 0;
}

#include <iostream>

auto power_of_2_func(int n) -> long {
  auto result = 1;
  while (n-- > 0) {
    result = result * 2;
  }
  return result;
}

auto power_of_2_recursive(int n) -> long {
  if (n == 0) return 1;
  return 2 * power_of_2_recursive(n - 1);
}

template <int N>
struct PowerOfTwo {
  // static const auto value = 2 * PowerOfTwo<N - 1>::value;
  // enum will not allocate
  enum { value = 2 * PowerOfTwo<N - 1>::value };
};

template <>
struct PowerOfTwo<0> {
  // static const auto value = 1;
  // enum will not allocate
  enum { value = 1 };
};

int main() {
  std::cout << "Using function : " << std::endl;
  std::cout << power_of_2_func(0) << std::endl;
  std::cout << power_of_2_func(1) << std::endl;
  std::cout << power_of_2_func(2) << std::endl;
  std::cout << power_of_2_func(3) << std::endl;
  std::cout << power_of_2_func(4) << std::endl;
  std::cout << power_of_2_func(5) << std::endl;
  std::cout << power_of_2_func(6) << std::endl;
  std::cout << power_of_2_func(7) << std::endl;
  std::cout << power_of_2_func(8) << std::endl;

  std::cout << "Using recursive function : " << std::endl;
  std::cout << power_of_2_recursive(0) << std::endl;
  std::cout << power_of_2_recursive(1) << std::endl;
  std::cout << power_of_2_recursive(2) << std::endl;
  std::cout << power_of_2_recursive(3) << std::endl;
  std::cout << power_of_2_recursive(4) << std::endl;
  std::cout << power_of_2_recursive(5) << std::endl;
  std::cout << power_of_2_recursive(6) << std::endl;
  std::cout << power_of_2_recursive(7) << std::endl;
  std::cout << power_of_2_recursive(8) << std::endl;

  std::cout << "Using template metaprograming " << std::endl;
  std::cout << PowerOfTwo<0>::value << std::endl;
  std::cout << PowerOfTwo<1>::value << std::endl;
  std::cout << PowerOfTwo<2>::value << std::endl;
  std::cout << PowerOfTwo<3>::value << std::endl;
  std::cout << PowerOfTwo<4>::value << std::endl;

  return 0;
}
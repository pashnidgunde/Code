#include <iostream>

long to_decimal(long binary) {
  return (binary == 0) ? 0 : 2 * to_decimal(binary / 10) + binary % 10;
}

// to_decimal(10) = 2 * to_decimal(1) + 0
// to_decimal(10) = 2 * 1 + 0;

template <unsigned long binary> struct Decimal {
  enum { value = 2 * Decimal<binary / 10>::value + binary % 10 };
};

template <> struct Decimal<0> {
  enum { value = 0 };
};

int main() {
  std::cout << to_decimal(0) << std::endl;
  std::cout << to_decimal(1) << std::endl;
  std::cout << to_decimal(10) << std::endl;
  std::cout << to_decimal(11) << std::endl;

  std::cout << Decimal<0>::value << std::endl;
  std::cout << Decimal<1>::value << std::endl;
  std::cout << Decimal<10>::value << std::endl;
  std::cout << Decimal<11>::value << std::endl;

  return 0;
}
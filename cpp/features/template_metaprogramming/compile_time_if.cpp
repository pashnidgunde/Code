#include <cassert>
#include <iostream>
#include <stdint.h>
#include <type_traits>

// compile time if
template <bool, typename TrueType, typename FalseType> struct _if {};

// specialize for true
template <typename TrueType, typename FalseType>
struct _if<true, TrueType, FalseType> {
  using type = TrueType;
};

// specialize for false
template <typename TrueType, typename FalseType>
struct _if<false, TrueType, FalseType> {
  using type = FalseType;
};

int main() {
  _if<true, int, double>::type int_number;
  _if<false, int, double>::type double_number;

  assert((std::is_same<decltype(int_number), int>::value));
  assert((std::is_same<decltype(int_number), int>::value));
  assert((std::is_same<decltype(double_number), double>::value));

  _if<true, int, void *>::type number(10);
  _if<false, int, void *>::type address_of_number(&number);

  using integral_ptr_t =
      _if<(sizeof(void *) > sizeof(uint32_t)), uint64_t, uint32_t>::type;

  integral_ptr_t converted_pointer =
      reinterpret_cast<integral_ptr_t>(address_of_number);
  std::cout << converted_pointer << std::endl;
}

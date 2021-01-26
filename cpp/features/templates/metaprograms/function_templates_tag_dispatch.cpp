#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>


// templates --> parametric polyomorphism
namespace pn
{
  namespace tmp
  {
    template <typename T>
    bool equal(const T& lhs, const T& rhs) {
      std::cout << "Generic == comparison" << std::endl;
      return lhs == rhs;
    }

    // NOTE :
    // Partial specialization can not be applied to functions
    // Error : error: non-class, non-variable partial specialization ‘equal<T*>’ is
    // not allowed template <typename T>
    // bool pn::tmp::equal<T*>(const T* lhs, const T* rhs)
    // {
    //   return *lhs == *rhs;
    // }

    template <typename T>
    bool equal(const T* lhs, const T* rhs) {
      std::cout << "Generic pointer values comparison" << std::endl;
      return *lhs == *rhs;
    }

    template <>
    bool equal<const int>(const int* lhs, const int* rhs) {
      std::cout << "Integer pointer comparison" << std::endl;
      return *lhs == *rhs;
    }

    template <>
    bool equal<double>(const double& lhs, const double& rhs) {
      std::cout << "This is double comparison" << std::endl;
      // should use googletest::almost pn::tmp::equal
      // or
      // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
      return fabs(lhs - rhs) < std::numeric_limits<double>::epsilon();
    }

    template <>
    bool equal<float>(const float& lhs, const float& rhs) {
      std::cout << "This is float comparison" << std::endl;
      return fabs(lhs - rhs) < std::numeric_limits<float>::epsilon();
    }

    template <>
    bool equal<const char>(const char* lhs, const char* rhs) {
      std::cout << "This is char* comparison" << std::endl;
      return strcmp(lhs, rhs) == 0;
    }
  }
}


namespace pn
{
  namespace tag_dispatch
  {
    // acts as dispatcher, based on type
    template<typename T>
    bool equal(T lhs, T rhs)
    {
      // constexpr bool is_floating_type = std::is_floating_point<T>::value;
      // using IsFloatingType = typename std::conditional<is_floating_type,std::true_type,std::false_type>::type;
      // return equal(lhs,rhs,IsFloatingType{});

      return equal(lhs,rhs,
                  std::conditional_t<std::is_floating_point<T>::value, std::true_type, std::false_type>{});
    }

    // floating point types
    template<typename T>
    bool equal(T lhs, T rhs, std::true_type)
    {
      std::cout << "Floating point tag dispatch" << std::endl;
      return true;
    }
    
    // for non floating
    // floating point types
    template<typename T>
    bool equal(T lhs, T rhs, std::false_type)
    {
      std::cout << "Non Floating point tag dispatch" << std::endl;
      return false;
    }
  }

}

int main() {

  // specializations
  std::cout << pn::tmp::equal(1, 1) << std::endl;
  std::cout << pn::tmp::equal(2.0, 2.0) << std::endl;
  std::cout << pn::tmp::equal(2.0f, 2.0f) << std::endl;
  std::cout << pn::tmp::equal("Hello", "Hello") << std::endl;
  int x = 0;
  int y = 0;
  std::cout << pn::tmp::equal(&x, &y) << std::endl;  // This defaults to generic int
                                            // comparison as pointers are const

  const int* p = &x;
  const int* q = &y;
  std::cout << pn::tmp::equal(p, q) << std::endl;

  // tag dispatch --> TO DO --> didnt compile --> why ?
  // std::cout << pn::tag_dispatch::equal(1, 1) << std::endl;
  // std::cout << pn::tag_dispatch::equal(2.0, 2.0) << std::endl;
  // std::cout << pn::tag_dispatch::equal(2.0f, 2.0f) << std::endl;

  return 0;
}

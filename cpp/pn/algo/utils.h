#pragma once
#include <iostream>

namespace pn {
namespace utils {
template <typename Iter> static void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << " " << *begin << " ";
    begin++;
  }

  std::cout << std::endl;
}

template <template <typename, typename...> class ContainerType,
          typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...> &c) {
  for (const auto &v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

template<typename T>
class RandomN {};

template<typename T>
class RandomN<int>
{
    public:
        RandomN() : _N(10), _lower_range(0), _upper_range(10) 
        {
        }
        RandomN(size_t N, int lower_range, int upper_range) :   
            _N(N), _lower_range(lower_range), _upper_range(upper_range)
        {
        }
        std::vector<int> operator()()
        {
            std::random_device rd;
            std::mt19937 e(rd()); // random engine
            std::uniform_int_distribution<> urng(_lower_range, _upper_range);

            std::vector<int> numbers;
            numbers.reserve(_N);
            std::generate_n(std::back_inserter(numbers), 
                _N+1,
                [unrg,&e]() {return unrg(e);});
            
            return numbers;
        }
    private:
        size_t _N = 10;
        int _lower_range = 0;
        int _upper_range = 10; 
};

} // namespace utils
} // namespace pn

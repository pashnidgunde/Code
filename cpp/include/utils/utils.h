#ifndef PN_UTILS_UTILS_HPP
#define PN_UTILS_UTILS_HPP

#include <algorithm>
#include <random>

namespace pn
{
    namespace utils
    {
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
    }
}


#endif
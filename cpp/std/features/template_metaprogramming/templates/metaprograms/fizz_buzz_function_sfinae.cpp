// ----------------------------------------------------------------------
// 1
// 2
// Fizz
// 4
// Buzz
// Fizz
// 7
// Multiples of 3 -- Fizz , Multiples of 7 -- Buzz
// ----------------------------------------------------------------------
#include <iostream>
#include <cassert>
namespace pn{
    namespace fizzbuzz_runtime{
        void fizzBuzz()
        {
            int number = 20;
            for (int i=1;i<=number;++i)
            {
                if (i%3 == 0 && i%5 ==0)
                {
                    std::cout << "FizzBuzz" << std::endl;
                    continue;
                }

                if (i%3==0)
                {
                    std::cout << "Fizz" << std::endl;
                    continue;
                }

                if (i%5 ==0)
                {
                    std::cout << "Buzz" << std::endl;
                    continue;
                }

                std::cout << i << std::endl;
            }
        }
    }
}

#include <utility>
#include <sstream>
#include <type_traits>
namespace pn {
    namespace fizzbuzz_compiletime {

        template<size_t BEGIN, size_t MAX, std::enable_if_t<(BEGIN > MAX)>* = nullptr>
        void make_fizz_buzz_impl(std::stringstream& os)
        {
            return;
        }

        template<size_t BEGIN, size_t MAX, std::enable_if_t<(BEGIN <= MAX)>* = nullptr> 
        void make_fizz_buzz_impl(std::stringstream& os)
        {
            std::cout <<__PRETTY_FUNCTION__ << std::endl;
            if (BEGIN%3 ==0 && BEGIN%5 ==0)
            {
                os << "FizzBuzz" << std::endl;
            }
            else if (BEGIN%3 ==0)
            {
                os << "Fizz" << std::endl;
            }
            else if (BEGIN%5 ==0)
            {
                os << "Buzz" << std::endl;
            }
            else
            {
                os << BEGIN << std::endl;
            }
            //if (BEGIN < MAX)
                make_fizz_buzz_impl<BEGIN+1,MAX>(os);
        }

        

        template<size_t MAX> 
        void make_fizz_buzz(std::stringstream& os)
        {
            make_fizz_buzz_impl<1,MAX>(os);
            std::cout << os.str() << std::endl;
        }
       
    }
}

int main()
{
    //pn::fizzbuzz_runtime::fizzBuzz();
    std::stringstream ss;
    pn::fizzbuzz_compiletime::make_fizz_buzz<5>(ss);
    //assert(ss.str() == R"(1)");
    return 0;
}
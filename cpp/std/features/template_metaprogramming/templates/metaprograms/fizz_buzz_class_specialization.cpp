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


                // std::cout <<  
                //    (i%3 == 0 && i%5 ==0) ?  "FizzBuzz" 
                //         : (i%3==0) ? "Fizz"
                //             : (i%5==0) ? "Buzz"
                //                 :   std::to_string(i);
            }
        }
    }
}

#include <utility>
#include <sstream>
#include <type_traits>
namespace pn {
    namespace fizzbuzz_compiletime {
        //----------------------------------------------------------
        // Tags are effective ways to solve this problem too
        // As following code couldnt compile, you can wrap an unnamed type into named type with tags
        // template<size_t MAX>
        // struct make_fizz_buzz_impl<MAX+1, MAX>
        // {
        //     static void impl(std::stringstream&) {}
        // }
        //----------------------------------------------------------

        // template<size_t N> struct NumTag{};

        // template<class NumTagBegin, class NumTagMax> struct make_fizz_buzz_impl;
        // template<size_t BEGIN, size_t MAX>
        // struct make_fizz_buzz_impl<NumTag<BEGIN>, NumTag<MAX>>
        // {
        //     static void impl(std::stringstream& os)
        //     {
        //         if (BEGIN%3 ==0 && BEGIN%5 ==0)
        //         {
        //             os << "FizzBuzz" << std::endl;
        //         }
        //         else if (BEGIN%3 ==0)
        //         {
        //             os << "Fizz" << std::endl;
        //         }
        //         else if (BEGIN%5 ==0)
        //         {
        //             os << "Buzz" << std::endl;
        //         }
        //         else
        //         {
        //             os << BEGIN << std::endl;
        //         }
        //         make_fizz_buzz_impl<NumTag<BEGIN+1>,NumTag<MAX>>::impl(os);
        //     }
        // };
        // template<size_t MAX>
        // struct make_fizz_buzz_impl<NumTag<MAX+1>, NumTag<MAX>>
        // {
        //     static void impl(std::stringstream&) {}
        // };

        template<size_t BEGIN, size_t MAX, class Enable = void>
        struct make_fizz_buzz_impl
        {
            static void impl(std::stringstream& os)
            {
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
                make_fizz_buzz_impl<BEGIN+1,MAX>::impl(os);
            }
        };
        template<size_t BEGIN, size_t MAX>
        struct make_fizz_buzz_impl<BEGIN, MAX, std::enable_if_t<(BEGIN > MAX)>>
        {
            static void impl(std::stringstream&) {}
        };

        template<size_t MAX> 
        void make_fizz_buzz(std::stringstream& os)
        {
            // make_fizz_buzz_impl<NumTag<1>,NumTag<MAX>>::impl(os);
            make_fizz_buzz_impl<1,MAX>::impl(os);
            std::cout << os.str() << std::endl;
        }
       
    }
}

int main()
{
    pn::fizzbuzz_runtime::fizzBuzz();
    //std::stringstream ss;
    //pn::fizzbuzz_compiletime::make_fizz_buzz<5>(ss);
    //assert(ss.str() == R"(1)");
    return 0;
}
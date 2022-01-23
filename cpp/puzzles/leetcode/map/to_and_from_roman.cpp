
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

const std::map<int, char> m_literals{{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};
const std::map<char, int> m_natural{{'I', 1}, {'V', 5}, {'X',10}, {'L',50}, {'C',100}, {'D',500}, {'M',1000}};

namespace pn
{
    namespace misc
    {
        size_t number_of_digits(size_t num)
        {
            size_t digits = 0;
            while (num > 0)
            {
                num = num / 10;
                digits++;
            }
            return digits;
        }

        long pow10l(long number)
        {
            auto result =1;
            while (number > 0)
            {
                result = result * 10;
                number--;
            }
            return result;
        }

        std::string toRomanLiterals(size_t num)
        {
            std::stringstream result;
            while (num > 0)
            {
                if (m_literals.find(num) != m_literals.end())
                {
                    result << m_literals.at(num);
                    break;
                }

                size_t num_of_digits = number_of_digits(num);
                auto min = pow10l(num_of_digits - 1);
                auto mid = pow10l(num_of_digits) / 2;

                if (m_literals.find(num + min) != m_literals.end())
                {
                    result << m_literals.at(min);
                    result << m_literals.at(min + num);
                    break;
                }

                if (num > mid)
                {
                    result << m_literals.at(mid);
                    num = num - mid;
                    continue;
                }

                if (num < mid)
                {
                    result << m_literals.at(min);
                    num = num - min;
                }
            }
            std::cout << result.str() << std::endl;
            return result.str();
        }
    } // namespace misc
} // namespace pn

namespace pn
{
    namespace misc
    {
        long toNatural(const std::string& roman)
        {
            size_t curr = 0l, sum = 0l, prev = 0l;
            for (char ch : roman)
            {
                curr = m_natural.at(ch);
                sum += (curr > prev) ? (curr - 2*prev) : curr;
                prev = curr;
            }
            return sum;
        }
    }
}

namespace vk
{
    namespace misc
    {
        std::string toRomanWithMagnitude(int num, char begin, char mid, char end)
        {
            if (num,0) return "";

            std::string b(1, begin);
            std::string m(1, mid);
            std::map<int,std::string> lookup;
            auto base=1;
            lookup[base] = b;
            lookup[base*2] = b+b;
            lookup[base*3] = b+b+b;
            lookup[base*4] = b+m;
            lookup[base*5] = m;
            lookup[base*6] = m+b;
            lookup[base*7] = m+b+b;
            lookup[base*8] = m+b+b+b;
            lookup[base*9] = b+end;

            return lookup[num];
        }
        const std::vector<char> m_literals{'I','V','X','L','C','D','M'};
        std::string toRoman(long number)
        {
            size_t index=0;
            std::vector<std::string> result;
            while(number > 0)
            {
                result.push_back(toRomanWithMagnitude(number%10, m_literals[index], m_literals[index+1], m_literals[index+2]));
                number =  number / 10;
                index = index + 2;
            }
            std::string s_result;
            for(auto riter = result.rbegin(); riter != result.rend(); riter++)
            {
                s_result.append(*riter);
            }
            return s_result;
        }
    }

}

TEST(Roman, toRomanPN)
{
    ASSERT_EQ(pn::misc::toRomanLiterals(1), "I");
    ASSERT_EQ(pn::misc::toRomanLiterals(4) , "IV");
    ASSERT_EQ(pn::misc::toRomanLiterals(9) , "IX");
    ASSERT_EQ(pn::misc::toRomanLiterals(100) , "C");
    ASSERT_EQ(pn::misc::toRomanLiterals(900) , "CM");
    ASSERT_EQ(pn::misc::toRomanLiterals(550) , "DL");
    ASSERT_EQ(pn::misc::toRomanLiterals(27) , "XXVII");
}

TEST(Roman, toRomanVK)
{
    ASSERT_EQ(vk::misc::toRoman(1) , "I");
    ASSERT_EQ(vk::misc::toRoman(4) , "IV");
    ASSERT_EQ(vk::misc::toRoman(9) , "IX");
    ASSERT_EQ(vk::misc::toRoman(100) , "C");
    ASSERT_EQ(vk::misc::toRoman(900) , "CM");
    ASSERT_EQ(vk::misc::toRoman(550) , "DL");
    ASSERT_EQ(vk::misc::toRoman(27) , "XXVII");
}

TEST(Roman,FromRomanPN)
{
    ASSERT_EQ(pn::misc::toNatural("I") , 1);
    ASSERT_EQ(pn::misc::toNatural("IV") , 4);
    ASSERT_EQ(pn::misc::toNatural("IX") , 9);
    ASSERT_EQ(pn::misc::toNatural("C") , 100);
    ASSERT_EQ(pn::misc::toNatural("CM") , 900);
    ASSERT_EQ(pn::misc::toNatural("DL") , 550);
    ASSERT_EQ(pn::misc::toNatural("XXVII") , 27);
}

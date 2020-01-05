#include <algorithm>
#include <iostream>
#include <vector>
#include "functors.h"

bool my_function_predicate(int x, int y) { return abs(x) == abs(y); }

int main() {
  std::vector<int> v1{1, 2, 3, 4};
  std::vector<int> v2{1, 2, 3, 4};

  std::cout << std::boolalpha << std::equal(v1.begin(), v1.end(), v2.begin())
            << std::endl;

  // This is false because the iter goes over first range
  std::cout << std::boolalpha
            << std::equal(v1.begin(), v1.end(), v2.begin(),
                          std::next(v2.begin(), 2))
            << std::endl;

  // This is false because end is specified and hence needs to be in range for
  // first sequnce
  std::cout << std::boolalpha
            << std::equal(v1.begin(), std::next(v1.begin(), 2), v2.begin(),
                          v2.end())
            << std::endl;

  // This is true for subrange check because the end of the second range is not
  // specified
  std::cout << std::boolalpha
            << std::equal(v1.begin(), std::next(v1.begin(), 2), v2.begin())
            << std::endl;

  // lambdas / callable objects are function objects
  auto func = [](int lhs, int rhs) { return lhs == rhs; };
  std::cout << std::boolalpha
            << std::equal(v1.begin(), v1.end(), v2.begin(), func) << std::endl;

  std::cout << std::boolalpha
            << std::equal(v1.begin(), v1.end(), v2.begin(), v2.end(),
                          pn::functors::equal<int>())
            << std::endl;

  std::vector<int> v_unsigned{1, 2, 3, 4};
  std::vector<int> v_signed{-1, -2, -3, -4};
  std::equal(v_signed.begin(), v_signed.end(), v_unsigned.begin(),
             my_function_predicate);

  //=================================================================================
  int myints[] = {20, 40, 60, 80, 100};           //   myints: 20 40 60 80 100
  std::vector<int> myvector(myints, myints + 5);  // myvector: 20 40 60 80 100

  // using default comparison:
  if (std::equal(myvector.begin(), myvector.end(), myints))
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  myvector[3] = 81;  // myvector: 20 40 60 81 100

  // using predicate comparison:
  if (std::equal(myvector.begin(), myvector.end(), myints,
                 my_function_predicate))
    std::cout << "The contents of both sequences are equal.\n";
  else
    std::cout << "The contents of both sequences differ.\n";

  return 0;
}
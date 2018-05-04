#include "is_sorted.hpp"
#include "functors.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

struct Emp
{
    int id;
    double salary;
};

bool operator < (const Emp& lhs , const Emp& rhs)
{
	// compare ids directly
	//return lhs.id < rhs.id;
	//
	//compare using comparator operator
	//pn::functors::less<int> op;
	//return op(lhs.id,rhs.id);
	//
	//club above two in one line
	return pn::functors::less<int> ()(lhs.id,rhs.id);
}

int main() {

  std::vector<int> x{1};
  std::vector<int> x1{1, 3, 2};
  std::vector<int> x2{1, 1, 1};
  std::vector<int> x4{4,3,2,1};
  std::vector<int> x3{};

  std::vector<Emp> employees { {35,100.100} , { 36, 125.40} };

  auto lhs = std::is_sorted(x.begin(), x.end());
  auto rhs = pn::algo::is_sorted(x.begin(), x.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  lhs = std::is_sorted(x1.begin(), x1.end());
  rhs = pn::algo::is_sorted(x1.begin(), x1.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  // This is how its diferent than standard is_sorted
  // standard less compares for less and equal whereas we use the functor
  // to specify which comparator to use
  lhs = std::is_sorted(x2.begin(), x2.end());
  rhs = pn::algo::is_sorted(x2.begin(), x2.end(), pn::functors::less<int>());
  assert(lhs != rhs);
  
  lhs = std::is_sorted(x2.begin(), x2.end());
  rhs = pn::algo::is_sorted(x2.begin(), x2.end(), pn::functors::less_equal<int>());
  assert(lhs == rhs);

  lhs = std::is_sorted(x3.begin(), x3.end());
  rhs = pn::algo::is_sorted(x3.begin(), x3.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  // This is how its diferent than standard is_sorted
  // standard less compares for less and equal whereas we use the functor
  // to specify which comparator to use
  lhs = std::is_sorted(x4.begin(), x4.end());
  rhs = pn::algo::is_sorted(x3.begin(), x3.end(), pn::functors::greater<int>());
  assert(lhs != rhs);


  // tests against the custom types
  lhs = std::is_sorted(employees.begin(), employees.end());
  rhs = pn::algo::is_sorted(employees.begin(), employees.end(), pn::functors::less<Emp>());
  assert(lhs == rhs);

  return 0;
}

#include "is_sorted.hpp"
#include "functors.h"
#include <algorithm>
#include <cassert>
#include <iostream>

int main() {
  std::vector<int> x{1};
  std::vector<int> x1{1, 3, 2};
  std::vector<int> x2{1, 1, 1};

  auto lhs = std::is_sorted(x.begin(), x.end());
  auto rhs = pn::algo::is_sorted(x.begin(), x.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  lhs = std::is_sorted(x1.begin(), x1.end());
  rhs = pn::algo::is_sorted(x1.begin(), x1.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  lhs = std::is_sorted(x2.begin(), x2.end());
  rhs = pn::algo::is_sorted(x2.begin(), x2.end(), pn::functors::less<int>());
  assert(lhs == rhs);

  return 0;
}

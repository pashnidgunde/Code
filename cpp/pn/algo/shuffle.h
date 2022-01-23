#pragma once

// shuffle randomly elements
// Algo:
//   for i from n-1 downto 1 do
//	j = random integer such that 0 <= j <=i
//	exchange a[i] and a[j]

#include "swap.h"
#include <stdlib.h>
#include <time.h>

template <typename Iter>
void shuffleUsingFisherYatesAlgo(Iter begin, Iter end) {
  srand(time(NULL));
  auto distance(std::distance(begin, end));
  for (auto i = distance - 1; i >= 1; --i) {
    auto j = rand() % i;
    pn::algo::swap(*(begin + i), *(begin + j));
  }
}

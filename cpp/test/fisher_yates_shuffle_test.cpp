// Program to test random shuffling of vector elements

#include <vector>
#include "algorithm.h"
#include "utils.h"

void shuffleUsingFisherYatesAlgo(std::vector<int>& v) {
  shuffleUsingFisherYatesAlgo(v.begin(), v.end());
}

int main() {
  std::vector<int> v{1, 5, 6, 9, 2, 3};
  pn::utils::print(v.begin(), v.end());
  shuffleUsingFisherYatesAlgo(v);
  pn::utils::print(v.begin(), v.end());

  return 0;
}

//
// Given an array of integers (0,1,2) sort the array in linear time and constant
// space. This is also known as dutch flag problem
// Naive solution is to use counting sort ( O(n*n) worst case)
//
// Alternative approach : three way partitioning O(n)

#include <vector>
#include "algo/sort/counting_sort.h"
#include "functors.h"
#include "partition.h"
#include "utils.h"

void threeWayPartition(std::vector<int> v) {
  int begin = 0;
  int mid = 0;
  int end = v.size() - 1;

  while (mid < end) {
    auto elem = v[mid];
    if (elem == 0) {
      pn::algo::swap(v[mid], v[begin]);
      begin++;
      mid++;
    }

    if (elem == 1) {
      mid++;
    }

    if (elem == 2) {
      pn::algo::swap(v[mid], v[end]);
      end--;
    }
  }
}

int main() {
  std::vector<int> v{2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0};
  pn::algo::countingSort(v.begin(), v.end(), pn::functors::less<int>());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));

  std::vector<int> v1{2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2,
                      2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0};
  pn::algo::partition(v1.begin(), v1.end(), pn::functors::less<int>());
  pn::utils::print<std::vector<int>::iterator>(std::begin(v1), std::end(v1));

  std::vector<int> v2{2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2,
                      2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0};
  threeWayPartition(v);
  pn::utils::print<std::vector<int>::iterator>(std::begin(v), std::end(v));

  return 0;
}
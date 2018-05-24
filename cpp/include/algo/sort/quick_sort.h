#pragma once
#include <algorithm>  // For rest other algos
#include "functors.h"
#include "partition.h"  // For partition

namespace pn {
namespace algo {
// In quick sort you have to find a pivot such that
// all elements to its left are lower than that of element at pivot
// and elements to its right are greater than element at pivot.
// Apply this same technique for sub arrays split in two at mid
// Method to split elements by comparing pivot element is called
// partitioning
template <typename Iter, typename Op>
void quickSort(Iter begin, Iter end, Op op) {
  if (begin < end) {
    // Partition elements and return pivot
    Iter pivot = pn::algo::partition(begin, end, op);
    // print after each partition
    // print(v);
    // quick sort by divide and conquer
    Iter prevToPivot = pivot;
    std::advance(prevToPivot, -1);
    Iter nextToPivot = pivot;
    std::advance(nextToPivot, 1);
    quickSort(begin, prevToPivot, op);
    quickSort(nextToPivot, end, op);
  }
}
}  // namespace algo
}  // namespace pn
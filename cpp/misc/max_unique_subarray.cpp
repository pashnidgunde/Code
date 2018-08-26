
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

// http://www.techiedelight.com/find-largest-sub-array-formed-by-consecutive-integers/

class MaxUniqueSubArray {
 public:
  static std::pair<int, int> find(const std::vector<int>& v) {
    std::unordered_map<int, int> m;
    auto size = v.size();
    auto count = 0, max_count = 0, begin = 0, end = (int)size - 1;
    std::pair<int, int> max_range(begin, end);

    for (auto i = 0u; i < size; ++i) {
      count++;
      if (m.find(v[i]) != m.end()) {
        count--;
        end = (i - 1 > 0) ? i - 1 : 0;
        if (count > max_count) {
          max_count = count;
          max_range.first = begin;
          max_range.second = end;
        }

        count -= (m[v[i]] - begin);

        begin = m[v[i]] + 1;
      }

      m[v[i]] = i;
    }

    return max_range;
  }
};

int main() {
  // Test case 1
  std::vector<int> v{2, 0, 2, 1, 4, 3, 1, 0};
  assert((MaxUniqueSubArray::find(v) == std::pair<int, int>(1, 5)));

  // Test case 2
  std::vector<int> v1{2};
  assert((MaxUniqueSubArray::find(v1) == std::pair<int, int>(0, 0)));

  // Test case 3
  std::vector<int> v2{2, 0, 1, 3};
  assert((MaxUniqueSubArray::find(v2) == std::pair<int, int>(0, 3)));

  char ch;
  std::cin >> ch;

  return 0;
}

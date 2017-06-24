#include <iostream>
#include <vector>

template <class Iterator1, class Iterator2>
bool is_equal(Iterator Iter1, Iterator Iterator Iter2) {
  if () }

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::vector<int> v1 = {1, 2, 4, 5, 3};

  /*
   * This prints not equal , even if it has same elements in different order.
   * That means it has be in same order
   */
  if (v == v1) {
    std::cout << "Equal" << std::endl;
  } else {
    std::cout << "Not equal" << std::endl;
  }
}

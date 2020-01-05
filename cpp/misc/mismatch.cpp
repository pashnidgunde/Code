/*
 * mismatch.cpp
 *
 *  Created on: 15-Jan-2017
 *      Author: rupa
 */

#include <iostream>
#include <vector>

/*
std::vector<int>::const_iterator mismatch(const std::vector<int>& v,
                                          const std::vector<int>& v1) {
  std::vector<int>::const_iterator i1 = v.begin();
  std::vector<int>::const_iterator i2 = v1.begin();

  while ((*i1 == *i2) && (i1 != v.end() && i2 != v1.end())) {
    i1++;
    i2++;
  }

  return i1;
}

*/
template <class Iter> Iter mismatch(Iter ib, Iter ie, Iter ib1, Iter ib2) {
  while ((*ib == *ib1) && (ib != ie && ib1 != ib2)) {
    ib++;
    ib1++;
  }

  return ib1;
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5};
  std::vector<int> v1{1, 2, 4, 4, 5};

  std::vector<int>::const_iterator i =
      mismatch(v.begin(), v.end(), v1.begin(), v1.end());
  if (i == v.end()) {
    std::cout << "No Mismatch";
  } else {
    std::cout << "Mismatch at " << *i;
  }

  return 0;
}

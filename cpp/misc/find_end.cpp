/*
 * find_end.cpp
 *
 *  Created on: 15-Jan-2017
 *      Author: rupa
 */

#include <iostream>
#include <vector>

std::vector<int>::reverse_iterator find_end(std::vector<int>& v,
                                            std::vector<int>& f) {
  typedef std::vector<int>::reverse_iterator Iter;

  Iter rbv = v.rbegin();
  for (; rbv != v.rend(); rbv++) {
    Iter rbf = f.rbegin();
    for (; rbf != f.rend(); rbf++) {
      if (*rbf == *rbv) {
        continue;
      } else {
        break;
      }
    }
    if (rbf == f.rend()) {
      break;
    }
  }

  return rbv;
}

int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 1, 2};
  std::vector<int> f{1, 2};

  std::vector<int>::reverse_iterator i = find_end(v, f);
}

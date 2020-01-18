#include <iostream>
#include <set>

// Task. The goal in this problem is to find the minimum number of coins needed
// to change the input value
//(an integer) into coins with denominations 1, 5, and 10.

// 28 = 10 + 10 + 5 + 1 + 1 + 1

int get_change(int m) {
  std::set<int> change{10, 5, 1};

  auto i = 0;
  auto coins = 0;
  while (m > 0) {
    if (m - change[i]) >= 0) {
        m -= change[i];
        coins++;
      }
    i++;
  }

  // write your code here
  return n;
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}

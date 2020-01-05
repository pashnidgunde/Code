
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  auto size = 0;
  auto obstacles = 0;

  std::cin >> size >> obstacles;
  const auto limits = size;

  std::vector<std::vector<int>> arr(limits, std::vector<int>(limits));

  for (auto i = 0; i < limits; i++) {
    for (auto j = 0; j < limits; j++) {
      arr[i][j] = 0;
    }
  }

  auto Qi = 0, Qj = 0;
  std::cin >> Qi >> Qj;

  auto r = Qi - 1;
  auto c = Qj - 1;
  arr[r][c] = 1;

  auto Oi = 0, Oj = 0;
  for (auto i = 0; i < obstacles; i++) {
    std::cin >> Oi >> Oj;
    arr[Oi - 1][Oj - 1] = 1;
  }

  auto count = 0;

  // 1. Same Row Reduce Cols
  for (auto j = c - 1; j >= 0; j--) {
    arr[r][j] == 0 ? count++ : j = 0;
  }
  std::cout << "count ::" << count;

  // 2. Same row increse cols
  for (auto j = c + 1; j < limits; j++) {
    arr[r][j] == 0 ? count++ : j = limits;
  }
  std::cout << "count ::" << count;

  // 3. Same Col Reduce Row
  for (auto i = r - 1; i >= 0; i--) {
    arr[i][c] == 0 ? count++ : i = 0;
  }
  std::cout << "count ::" << count;

  // 4. Same Col increase Row
  for (auto i = r + 1; i < limits; i++) {
    arr[i][c] == 0 ? count++ : i = limits;
  }
  std::cout << "count ::" << count;

  // left diagonal down
  for (auto i = r - 1, j = c - 1; (i >= 0 && j >= 0); i--, j--) {
    arr[i][j] == 0 ? count++ : i = limits;
  }
  std::cout << "count ::" << count;

  // right diagonal up
  for (auto i = r + 1, j = c + 1; (i < limits && j < limits); i++, j++) {
    arr[i][j] == 0 ? count++ : i = limits;
  }
  std::cout << "count ::" << count;

  // right diagonal down
  for (auto i = r - 1, j = c + 1; (i >= 0 && j < limits); i--, j++) {
    arr[i][j] == 0 ? count++ : i = 0;
  }
  std::cout << "count ::" << count;

  // left diagonal up
  for (auto i = r + 1, j = c - 1; (i < limits && j >= 0); i++, j--) {
    arr[i][j] == 0 ? count++ : i = limits;
  }
  std::cout << "count ::" << count;

  std::cout << count;

  return 0;
}

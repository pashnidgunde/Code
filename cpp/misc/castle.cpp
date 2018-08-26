// www.hackerrank.com/challenges/castle-on-the-grid?utm_campaign=challenge-recommendation&utm_medium=email&utm_source=24-hour-campaign

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<bool>>;

void visit(const int &size, int i, int j, const int &di, const int &dj,
           const Matrix &matrix, Matrix &v, int count, int gi, int gj,
           int &final_count) {
  // check if crossing the boundary
  if (j == size || j == -1 || i == -1 || i == size) {
    return;
  }

  // Check if already visisted or there is no path
  if (!matrix[i][j] || v[i][j]) {
    return;
  }

  // mark it visited
  v[i][j] = true;

  if (i != gi && j != gj) {
    gi = i;
    gj = j;
    std::cout << "Moved to ::" << gi << gj << std::endl;
    count += 1;
  }

  // Check if you reached destination
  if (i == di && j == dj) {
    count += 1;
    if (final_count > count) {
      final_count = count;
      return;
    }
  }

  // Move down
  visit(size, i, j + 1, di, dj, matrix, v, count, gi, gj, final_count);
  // Move Left
  visit(size, i - 1, j, di, dj, matrix, v, count, gi, gj, final_count);
  // Move right
  visit(size, i + 1, j, di, dj, matrix, v, count, gi, gj, final_count);
  // Move up
  visit(size, i, j - 1, di, dj, matrix, v, count, gi, gj, final_count);
}

int main() {
  auto size = 0;
  std::cin >> size;
  Matrix matrix(size, std::vector<bool>(size));
  Matrix v(size, std::vector<bool>(size));

  std::string str;
  for (auto i = 0; i < size; i++) {
    std::cin >> str;
    auto j = 0;
    for (auto ch : str) {
      matrix[i][j] = (ch == '.');
      v[i][j] = false;
      j++;
    }
  }

  auto bi = 0, bj = 0;
  auto di = 0, dj = 0;

  std::cin >> bi >> bj >> di >> dj;

  auto final_count = size * size;
  visit(size, bi, bj, di, dj, matrix, v, 0, bi, bj, final_count);
  std::cout << final_count;

  return 0;
}

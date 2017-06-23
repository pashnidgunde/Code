

#include <iostream>

int matrix[5][7] = {{0, 1, 1, 1, 0, 0, 1},
                    {1, 0, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 0, 1},
                    {1, 0, 0, 1, 0, 0, 0},
                    {1, 0, 0, 0, 1, 0, 0}};

int v[5][7];

int visit(int i, int j) {
  if (j == 7 || j == -1 || i == -1 || i == 6 || matrix[i][j] == 0 ||
      v[i][j] == 1)
    return 0;

  v[i][j] = 1;

  return 1 + visit(i - 1, j) + visit(i, j + 1) + visit(i + 1, j) +
         visit(i, j - 1);
}

int getMaxCountofAdjacent1() {

  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 7; j++) {
      v[i][j] = 0;
    }
  }

  int max_count = 0;

  for (auto i = 0; i < 5; i++) {
    for (auto j = 0; j < 7; j++) {
      if (v[i][j] == 0 && matrix[i][j] == 1) {
        auto count = visit(i, j);
        if (count > max_count)
          max_count = count;
      }
      v[i][j] = 1;
    }
  }

  return max_count;
}

int main() {
  getMaxCountofAdjacent1();
  return 0;
}

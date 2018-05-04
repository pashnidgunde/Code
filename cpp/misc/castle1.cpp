// www.hackerrank.com/challenges/castle-on-the-grid?utm_campaign=challenge-recommendation&utm_medium=email&utm_source=24-hour-campaign

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

using Matrix = std::vector<std::vector<bool>>;

struct Point {
  int i = 0, j = 0, distance = 0;
  explicit Point(int pi, int pj, int d) : i(pi), j(pj), distance(d) {}
  bool operator==(const Point &other) { return (i == other.i && j == other.j); }
};

void update_visited(std::list<Point> &neighbours, Matrix &visited, const int &i,
                    const int &j, const int &distance) {
  if (!visited[i][j]) {
    neighbours.emplace_back(Point(i, j, distance));
    visited[i][j] = true;
  }
}

std::list<Point> getNeighbours(const Matrix &matrix, const Point &p,
                               Matrix &v) {

  std::list<Point> neighbours;

  // Step 1. Go Right
  int i = p.i;
  int j = p.j + 1;
  int size = matrix.size();
  while (j < size && matrix[i][j]) {
    update_visited(neighbours, v, i, j, p.distance + 1);
    j++;
  }

  // Step 2. Go to Bottom
  i = p.i + 1;
  j = p.j;
  while (i < size && matrix[i][j]) {
    update_visited(neighbours, v, i, j, p.distance + 1);
    i++;
  }

  // Step 3. Go to Left
  i = p.i;
  j = p.j - 1;
  while (j >= 0 && matrix[i][j]) {
    update_visited(neighbours, v, i, j, p.distance + 1);
    j--;
  }

  // Step 4. Go to Top
  i = p.i - 1;
  j = p.j;
  while (i >= 0 && matrix[i][j]) {
    update_visited(neighbours, v, i, j, p.distance + 1);
    i--;
  }

  return std::move(neighbours);
}

int visit(const Matrix &matrix, const Point &start, const Point &dest) {
  Matrix v(matrix.size(), std::vector<bool>(matrix.size()));
  for (size_t i = 0; i < v.size(); i++) {
    for (size_t j = 0; j < v.size(); j++) {
      v[i][j] = false;
    }

    std::queue<Point> points;
    points.push(start);

    while (true) {
      Point &p = points.front();
      std::list<Point> neighbours = getNeighbours(matrix, p, v);
      if (std::find(neighbours.begin(), neighbours.end(), dest) !=
          neighbours.end()) {
        return p.distance + 1;
      }

      for (auto neighbour : neighbours) {
        points.push(neighbour);
      }

      points.pop();
    }
  }

  return 0;
}

int main() {

  auto size = 0;
  std::cin >> size;
  Matrix matrix(size, std::vector<bool>(size));

  std::string str;
  for (auto i = 0; i < size; i++) {
    std::cin >> str;
    auto j = 0;
    for (auto ch : str) {
      matrix[i][j] = (ch == '.');
      j++;
    }
  }

  auto bi = 0, bj = 0, di = 0, dj = 0;
  std::cin >> bi >> bj >> di >> dj;

  std::cout << visit(matrix, Point(bi, bj, 0), Point(di, dj, 0));

  return 0;
}

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

// Program to calculate maximum number of paths
// starting point is 0,0 and end point is max-1,max-1
// Possible directions : right and down.

// TBD : Convert it to vector
int matrix[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

// Naive algorithm that visits each path to sum up
int max_paths_recursive(int row, int col) {
  // if path is blocked return 0
  if (matrix[row][col] == 0)
    return 0;

  // if beyond the boundary, return 0
  if (row == 3 || col == 3)
    return 0;

  // if destination , there exists a path, return 1
  if (row == 2 && col == 2)
    return 1;

  // do it for each down and right places.
  return max_paths_recursive(row + 1, col) + max_paths_recursive(row, col + 1);
}

// Here we memorize the paths and the distance at that path

// Influenced from ::
// https://stackoverflow.com/questions/32685540/c-unordered-map-with-pair-as-key-not-compiling
// Only for pairs of std::hash-able types for simplicity.
// You can of course template this struct to allow other hash functions
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // Mainly for demonstration purposes, i.e. works but is overly simple
    // In the real world, use sth. like boost.hash_combine
    return h1 ^ h2;
  }
};

// Memoization technique to store the value of previously computed values in
// hash table
using RowValPair = std::pair<int, int>;
// Result case that there is a path at 2,2 of dist 1
std::unordered_map<RowValPair, int, pair_hash> dist{{{2, 2}, 1}};

int max_path_recursive_memoization(int row, int col) {
  // if path is blocked return 0
  if (matrix[row][col] == 0)
    return 0;

  // if beyond the boundary, return 0
  if (row == 3 || col == 3)
    return 0;

  // find , if found no need to compute downpath
  auto it = dist.find({row, col});
  if (it != dist.end())
    return it->second;

  // compute and store it in memory
  int d = max_path_recursive_memoization(row + 1, col) +
          max_path_recursive_memoization(row, col + 1);
  dist[{row, col}] = d;
  return d;
}

// Third : Bottom up approach
int max_path_bottom_up(int row, int col) {
  for (int i = row; i >= 0; --i) {
    for (int j = col; j >= 0; --j) {
      if (i + 1 > 2 || j + 1 > 2)
        matrix[i][j] = 1;
      else
        matrix[i][j] = matrix[i + 1][j] + matrix[j + 1][i];
    }
  }

  return matrix[0][0];
}

int main() {
  std::cout << max_paths_recursive(0, 0);
  std::cout << max_path_recursive_memoization(0, 0);
  std::cout << max_path_bottom_up(2, 2);
}

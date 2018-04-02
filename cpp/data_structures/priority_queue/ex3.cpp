// C++ implementation to count ways to
// sum up to a given value N
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

// function to count the total number
// of ways to sum up to 'N'
int countWays(int arr[], int m, int N) {
  int count[N + 1];
  memset(count, 0, sizeof(count));

  // base case
  count[0] = 1;

  // count ways for all values up to 'N'
  // and store the result
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < m; j++) {
      // if i >= arr[j] then
      // accumulate count for value 'i' as
      // ways to form value 'i-arr[j]'
      if (i >= arr[j]) count[i] += count[i - arr[j]];
    }
  }

  for (int i = 0; i <= N; i++) {
    std::cout << count[i] << " ,";
  }

  // required number of ways
  return count[N];
}

// Driver program to test above
int main() {
  int arr[] = {2, 3};
  int m = sizeof(arr) / sizeof(arr[0]);
  int N = 10;
  cout << "Total number of ways = " << countWays(arr, m, N);
  return 0;
}
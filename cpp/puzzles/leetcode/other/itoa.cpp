/*
 * itoa.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <iostream>

void reverse(char arr[], int len) {
  for (int i = 0; i < len; i++, len--) {
    char ch = arr[i];
    arr[i] = arr[len];
    arr[len] = ch;
  }
}

void my_itoa(int number, char arr[]) {
  int num = number;
  char ch;
  int i = 0;
  while (num > 0) {
    ch = num % 10 + '0';
    arr[i++] = ch;
    num = num / 10;
  }
  reverse(arr, i - 1);
  arr[i] = '\0';
}

int main() {
  char arr[100];

  my_itoa(100, arr);
  std::cout << arr;

  return 0;
}

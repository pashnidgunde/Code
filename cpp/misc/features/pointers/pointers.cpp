/*
 * pointers.cpp
 *
 *  Created on: 10-Aug-2016
 *      Author: rupa
 */

#include <iostream>
void value(int *ptr) { *ptr = 0; }

void value(const char *ptr) { *ptr = "hello1"; }

int main() {
  char *hello = "hello";
  int x = 20;
  int *ptr = &x;
  value(ptr);
  value(hello);
  std::cout << x;
  std::cout << *ptr;

  return 0;
}

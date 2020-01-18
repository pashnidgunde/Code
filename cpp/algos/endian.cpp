/*
 * endian.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <iostream>
bool is_little_endian() {
  int i = 1;
  char *ch = (char *)&i;

  return (*ch == 1);
}

int main() { std::cout << "Endian :: " << is_little_endian(); }

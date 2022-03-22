/*
 * lowest_bit_set.cpp
 *
 *  Created on: 18-Jan-2017
 *      Author: rupa
 */

#include <iostream>

int position_of_set_bit(int number) {
  auto position = 0;
  while (number) {
    if ((number & 1))
      break;
    number = number >> 1;
    position++;
  }

  return position;
}

int main() { std::cout << "Position of set bit" << position_of_set_bit(256); }

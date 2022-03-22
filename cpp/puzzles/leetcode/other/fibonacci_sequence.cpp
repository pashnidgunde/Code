/*
 * fibonacci_sequence.cpp
 *
 *  Created on: 17-Jan-2017
 *      Author: rupa
 */

#include <iostream>

void Fibonacci(int num) {
  int num1 = 0, num2 = 1, result = 0;

  for (int i = 0; i < num; i++) {
    if (i < 2) {
      result = i;
    } else {
      result = num1 + num2;
      num1 = num2;
      num2 = result;
    }
    std::cout << result << ",";
  }
}

int main() {
  std::cout << "Enter Number :";
  int num;

  std::cin >> num;
  Fibonacci(10);
}

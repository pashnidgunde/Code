#include <iostream>

// C++ 03

enum MANGO { RED_MANGO, YELLOW_MANGO, GREEN_MANGO };

enum Apple { RED_APPLE, YELLOW_APPLE, GREEN_APPLE };

// In C++11 , you can have same names under different classes
// For example , RED in CPP11_Mango name is same in CPP11_Apple
// But, you can not have same names in enum in C++03
// hence you have GREEN_APPLE and GREEN_MANGO seperately and not
// just GREEN

enum class CPP11_Mango { RED, YELLOW, GREEN };

enum class CPP11_Apple { RED, YELLOW, GREEN };

int main() {
  // C++03 code
  int redMango = MANGO::RED_MANGO;
  int redApple = Apple::RED_APPLE;
  if (redMango == redApple) {
    std::cout << "Orange == Apple ( This is not fair )";
  }

  // C++ 11 code ( Compilation error)

  CPP11_Mango redMangoCpp11 = CPP11_Mango::RED;
  CPP11_Apple redAppleCpp11 = CPP11_Apple::RED;

  // Below code will result in compilation error
  // enumerator.cpp:53:24: error: invalid operands to binary expression
  // ('CPP11_Mango' and 'CPP11_Apple')
  if (redMangoCpp11 == redAppleCpp11) {
    std::cout << "Orange == Apple ( This is not fair )";
  }

  return 0;
}

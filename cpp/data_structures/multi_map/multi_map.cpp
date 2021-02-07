#include <iostream>
#include <map>

int main() {
  std::multimap<int, int> buy;
  std::multimap<int, int, std::greater<int>> sell;

  buy.insert(std::pair<int, int>(1, 1));
  buy.insert(std::pair<int, int>(1, 2));
  buy.insert(std::pair<int, int>(0, 1));
  buy.insert(std::pair<int, int>(0, 3));

  /*
  for (auto elem : buy)
  {
          std::cout << "Key : " << elem.first << "Value : " << elem.second;
  }
  */

  sell.insert(std::pair<int, int>(10, 1000));
  sell.insert(std::pair<int, int>(10, 900));
  sell.insert(std::pair<int, int>(9, 500));
  sell.insert(std::pair<int, int>(10, 400));

  for (auto elem : sell) {
    std::cout << "Key : " << elem.first << "Value : " << elem.second;
  }
}

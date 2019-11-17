#include <iostream>
#include <sstream>
#include <thread>

std::string very_long_string = "";
using namespace std;

void reverse(long size, char *begin) {
  char *end = begin + size;

  while (begin < end) {
    std::swap(*(begin++), *(end--));
  }
}
int main() {

  ifstream file("./new_file.txt");
  // ifstream file("./result.log");
  file >> very_long_string;

  reverse(very_long_string.size(), (char *)very_long_string.c_str());

  // std::cout << very_long_string;
}

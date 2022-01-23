#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <std::string> v{"1-20200114", "9-20200114", "10-20200114", "99-20200114", "100-20200114"};
    auto it = std::max_element(v.begin(),v.end());
    std::cout << *it;
    return 0;
}


#include <iostream>
#include <string>


int main()
{
    using namespace std::literals;
    std::string s ="Hello\0\0World";
    std::cout << s << " " << s.size() << std::endl;

    std::string s1 = "Hello\0\0World"s;
    std::cout << s1 << " " << s1.size() << std::endl;
}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>


int main()
{
    // input 
    std::vector<std::string> strs;
    while ( std::cin >> str )
    {
        strs.push_back(str);
    }
  
    // sort
    std::sort (strs.begin(),strs.end());

    // print
    std::copy(strs.begin(),strs.end(),std::ostream_iterator<std::string> ( std::cout,"\n"));

    return 0;
}

#include <string>
#include <iostream>
using namespace std;

void combination( const std::string& str)
{
    size_t size = str.size();
    
    for ( int i = 0;i < size ; i++)
    {
        
        for ( int offset = 0; offset < size ; offset++ )    
        {
            std::cout << str.substr(i,offset) << std::endl;
        }
        
    }
}

int main( int argc, char **argv) {

   string str = "968";
   std::cout << str.substr(0,0);
   std::cout << str.substr(0,1);
   std::cout << str.substr(0,2);
   //combination(str);
   return 0;
}
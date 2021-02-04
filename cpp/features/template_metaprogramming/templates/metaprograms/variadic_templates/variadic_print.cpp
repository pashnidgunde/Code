#include <iostream>

void print(std::ostream& ostr)
{
    std::cout << std::endl;
}

template<typename First, typename ...Args>
void print(std::ostream& ostr, First first, Args... args)
{
    ostr << first;
    if(sizeof...(args) > 0)
    {
        ostr << " ,";
    }
    print(ostr,args...);
}

template<typename... Args>
void print_non_recursive(std::ostream& ostr, Args... args)
{
    // using comma operator that expands to intializer list
    ((ostr << args << (sizeof...(args) > 0 ? " ,"  : "\n")),...);
    //std::cout << std::endl;
}

int main()
{
    print(std::cout , 1,2,3,4);
    print_non_recursive(std::cout,1,2,3,4);
}
#include <iostream>
#include <vector>

template<typename It, typename Pred>
bool Contains(It begin, It end, Pred p)
{
    for (; begin != end; ++begin)
    {
        if (p(*begin)) return true;
    }
    return false;
}

struct ContainsTwo
{
    //warning: use of 'auto' in parameter declaration only available with -fconcepts
    //bool operator()(const auto& elem) { return elem == 2;}
    bool operator()(const int& elem) { return elem == 2;}
};


int main()
{
    std::vector<int> v{1,2,3,4};
    std::cout << Contains(v.begin(),v.end(),[](const auto& elem) { return elem == 2; }) 
        << std::endl;
    
    std::cout << Contains(v.begin(),v.end(),ContainsTwo()) 
        << std::endl;
    return 0;
}
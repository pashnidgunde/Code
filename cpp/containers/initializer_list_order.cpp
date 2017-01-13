#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>




class boVector
{

    public:
        int x;  // aggregate initializer ( third preference for compiler to resolve)

    public:
        boVector(const int& other_x) : x(other_x)    // second preference
        {

        }

        boVector(const std::initializer_list<int> & other_list)   // First preference
        {
            x = *(other_list.begin());
        }

        void print()
        {
            std::cout << x;
        }

};


int main()
{
    // Note that initializer list is passed in { }
    // In this case , first preference is constructor with initalizer list
    // Second preference is the constructor with single arughement
    // Thir pref is the aggregate intializer
    boVector v{3};
    v.print();
   
    return 0;
}

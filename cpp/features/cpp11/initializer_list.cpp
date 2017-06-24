#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>

class boVector
{
    private:
        std::vector<int> vec;
    public:
    boVector(const std::initializer_list<int>& list) : vec(list)
    {

    }

    void print()
    {
        // ranged for
        for(auto const& elem : vec)
        {
            std::cout << elem;
        }
    }

};


int main()
{
    // Note that initializer list is passed in { }
    boVector justlikeVector{1,2,3,3,4,5};
    justlikeVector.print();

    return 0;
}

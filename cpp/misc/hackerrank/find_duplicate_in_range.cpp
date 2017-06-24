
#include <iostream>
#include <unordered_set>
#include <cassert>
#include <vector>
#include <stdlib.h>


// Please note that this will only work in a range with only one duplicate

class FindDuplicateElementInARange
{
    public:

        // Use of unordered map 
        // Complexity :: O(N) , space complexity O(N)
        static int find_using_unordered_set(const std::vector<int>& elements)
        {
            std::unordered_set<int> m;
            for (const auto& element : elements)
            {
                if (m.find(element) != m.end())
                {
                    return element;
                }

                m.insert(element);
            }

            return -1;
        }

        // Here the idea is to negate the nunmber of a particular index.
        // So if a number is negated already , then its the repeating number.
        // Easy ? Hell  No !!!
        static int find_using_negating_numbers(std::vector<int> elements)
        {
            for ( const auto& element : elements)
            {
                // Absolute is required because the negative subscript in array 
                // is not guaranteed.
                if (elements[ abs(element) -1 ]  > 0 )
                    elements[ abs(element) -1 ] *= -1;
                else
                    return element;
            }

            return -1;
        }


};







int main()
{

    std::vector<int> v{1,2,3,4,4};
    std::vector<int> v1{1,1,2,3,4,5};
   
    assert(FindDuplicateElementInARange::find_using_unordered_set(v) ==  4);
    assert(FindDuplicateElementInARange::find_using_unordered_set(v1) ==  1);
    assert(FindDuplicateElementInARange::find_using_negating_numbers(v) ==  4);
    assert(FindDuplicateElementInARange::find_using_negating_numbers(v1) ==  1);

    char ch;
    std::cin >> ch;

    return 0;
}

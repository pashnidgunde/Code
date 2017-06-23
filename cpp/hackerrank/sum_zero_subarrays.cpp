/* This is the first time i will be using an unordered map

*/

#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>

class SubArrayCountForGivenSum
{
    public:
        // Complexity : O(N*N)
        static int naive_approach(const std::vector<int>& v, const int& for_sum) {
            auto size = v.size();
            auto count = 0u;

            for (auto i = 0u; i < size; ++i ) {
                auto sum = 0;
                for ( auto j = i; j < size; ++j ) {
                    sum += v[j];
                    if ( sum  == for_sum ) 
                    { 
                        count++;
                    }
                }
            }

            return count;
        }

        // using unorded multimap
        static int better_approach(const std::vector<int>& v, const int& for_sum) {
            std::unordered_multimap<int,int> m;
            auto size = v.size();
            auto count = 0u;

            // To check if the number is available at a particular index
            m.insert(std::make_pair( for_sum,-1));
            auto sum = 0u;

            for (auto i = 0u; i <size; ++i ) {
                sum += v[i];
                auto it = m.find( sum + for_sum);
                
                // Check if there are numbers matching the current number in map
                // Find all matching numbers and increment count by that number.
                // Note, you first find the number and then look for the number 
                // in by incrementing the iterator. 
                while (it != m.end() && (it->first == (sum + for_sum))) {
                    count ++;
                    it++;
                }
                m.insert(std::make_pair(sum,i));
            }
        
            return count;
            
        }
};

int main()
{
    std::vector<int> arr { 4, 2, -3, -1, 0, 4 };
    int count1 = SubArrayCountForGivenSum::naive_approach(arr,0);
    int count2 = SubArrayCountForGivenSum::better_approach(arr,0);
    
    std::vector<int> arr1 { 3, 4, -7, 3, 1, 3, 1, -4, -2, -2 };
    int count3 = SubArrayCountForGivenSum::naive_approach(arr1,0);
    int count4 = SubArrayCountForGivenSum::better_approach(arr1,0);

    std::vector<int> arr2 { 0,0,0};
    int count5 = SubArrayCountForGivenSum::naive_approach(arr2,0);
    int count6 = SubArrayCountForGivenSum::better_approach(arr2,0);


    assert(count1 == 2);
    assert(count2 == 2);
    assert(count3 == 6);
    assert(count4 == 6);
    assert(count5 == 6);
    assert(count6 == 6);

    char ch;
    std::cin >> ch;
    return 0;

}



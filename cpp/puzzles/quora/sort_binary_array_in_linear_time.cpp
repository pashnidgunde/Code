//https://www.techiedelight.com/sort-binary-array-linear-time/

#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

void print_vector(const std::vector<int>& v)
{
    for (const auto& elem : v)
    {
        std::cout << elem << ", " ;
    }
    std::cout << "\n";
}

// using std::partition 
void sort_binary_array_in_linear_time_using_partition(std::vector<int> v)
{
    std::partition(v.begin(),v.end(),[](const auto& elem) { return elem == 0; });
    print_vector(v);
}

void sort_binary_array_in_linear_time(std::vector<int>& v)
{
    if (v.empty()) return;
    
    auto begin_it = std::begin(v);
    auto end_it = std::end(v) - 1;

    while (begin_it < end_it)
    {
        if (*begin_it == 1)
        {
            std::iter_swap(begin_it,end_it);
            //std::swap(*begin_it,*end_it);
            end_it--;
            continue;
        }
        begin_it++;
    }
}

int main()
{
    {
        std::vector<int> v{};
        print_vector(v);
        sort_binary_array_in_linear_time_using_partition(v);
        sort_binary_array_in_linear_time(v);
        print_vector(v);
        std::cout << "---------------" << std::endl;
    }

    {
        std::vector<int> v{1,1,0,0,1};
        print_vector(v);
        sort_binary_array_in_linear_time_using_partition(v);
        sort_binary_array_in_linear_time(v);
        print_vector(v);
        std::cout << "---------------" << std::endl;
    }

    {
        std::vector<int> v{0,1,0,1,0};
        print_vector(v);
        sort_binary_array_in_linear_time_using_partition(v);
        sort_binary_array_in_linear_time(v);
        print_vector(v);
        std::cout << "---------------" << std::endl;
    }

    {
        std::vector<int> v{1,1,1,0,0,0};
        print_vector(v);
        sort_binary_array_in_linear_time_using_partition(v);
        sort_binary_array_in_linear_time(v);
        print_vector(v);
        std::cout << "---------------" << std::endl;
    }


    return 0;
}
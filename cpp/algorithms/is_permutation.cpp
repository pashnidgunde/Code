#include <iostream>
#include <vector>

bool is_permutation(const std::vector<int>&from , const std::vector<int>& in)
{
    auto  std::begin(from);
    auto end_from = std::end(from);
    auto begin_in  = std::begin(in);
    auto end_in = std::end(in);

    for (const auto& begin_from = from.begin(), begin_from != from.end(); begin_from++)
    {
        if (*begin_from == *begin_in)
        {
            *begin_in++;
        }
        else
        {
            break;
        }
    }

    


}


int main()
{
    std::vector<int> from{1,2,3,4,5};
    std::vector<int> in{1,2,3,4,5};

    is_p




}
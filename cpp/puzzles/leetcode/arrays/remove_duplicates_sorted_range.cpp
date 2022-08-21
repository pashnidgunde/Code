#include <vector>
#include <cassert>

int rem_dup_from_sorted_vec(std::vector<int>& i)
{
    if (i.empty()) return 0;

    int bi = 0;
    int ni = 0;
    int count = 1;
    while(ni < i.size())
    {
        if (i[bi] != i[ni])
        {
            bi++;
            i[bi] = i[ni];
            count++;
        }
        ni++;            
    }

    return count;
}

int main()
{
    {
        std::vector<int> v{};
        assert((rem_dup_from_sorted_vec(v)) == 0);
    }
    
    {
        std::vector<int> v{1};
        assert((rem_dup_from_sorted_vec(v)) == 1);
    }

    {
        std::vector<int> v{1,1};
        assert((rem_dup_from_sorted_vec(v)) == 1);
    }

    {
        std::vector<int> v{1,2};
        assert((rem_dup_from_sorted_vec(v)) == 2);
    }

    {
        std::vector<int> v{1,1,2,2};
        assert((rem_dup_from_sorted_vec(v)) == 2);
    }

    return 0;   
}
#include <vector>
#include <iostream>
#include <cassert>
#include <optional>

template<typename Iter, typename T>
std::optional<Iter> findFirstDuplicate(Iter begin, Iter end, T low, T high)
{
    auto size = std::distance(begin, end);
    std::vector<bool> visited;
    visited.resize(size,0);

    while(begin != end)
    {
        if (std::greater(*begin, high)) continue;
        if (std::less(*begin, low)) continue;
        if (*begin == visited[*begin]) return begin;
        visited[*begin] = true;

        begin++;
    }

    return nullopt;
}

struct X
{
    int x;
};

bool operator < (const X& lhs, const X& rhs)
{
    return lhs.x < rhs.x;
}

bool operator > (const X& lhs, const X& rhs)
{
    return lhs.x > rhs.x;
}

std::optional<int> findFirstDuplicate(const std::vector<int>& v, int low = 0, int high=1000)
{
    auto it = findFirstDuplicate(v.begin(), v.end(), low, high);
    return (it != std::nullopt) ? *it.value() : std::optional<int>();
}


int main()
{
    {
        std::vector<int> i{1,1,1,1};
        assert(findFirstDuplicate(i) == 1);
    }

    {
        std::vector<int> i{1,2,3,4};
        assert(findFirstDuplicate(i) == -1);
    }

    return 0;
}


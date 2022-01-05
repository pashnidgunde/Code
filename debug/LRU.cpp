#include <queue>
#include <deque>
#include <set>
#include <algorithm>
#include <list>
#include <iostream>
#include <sstream>

// template <typename T, int MaxLen, typename Container=std::deque<T>>
// class FixedQueue : public std::queue<T, Container> {
// public:
//     void push(const T& value) {
//         if (this->c.)
//         if (this->size() == MaxLen) {
//            this->c.pop_front();
//         }
//         std::queue<T, Container>::push(value);
//     }


// };

// template<typename T, int MaxLen=5>
// class LRUCache : public FixedQueue<T,MaxLen>
// {
//     public:
//     void insert(const T& value)
//     {
//         if ()
//         if (c.size() == MaxLen)
//         {

//         }
//     }

//     std::queue<char,std::vector<T>> c;

// };

std::string foo(std::string s)
{
    std::list<char> cache;
    for (int i=0; i<s.size(); i++)
    {
        auto c = s[i];
        auto it = std::find(cache.begin(), cache.end(), c);
        if ( it != cache.end())
        {
            cache.remove(c);
            cache.push_back(c);
            continue;
        }

        if (cache.size() == 5) {
            cache.pop_front();
        }
        cache.push_back(c);
    }

    std::stringstream ss;
    for (auto c : cache)
    {
        ss << c << "-";
    }

    std::string r = ss.str();
    r.pop_back();
    return r;
}

int main()
{
    std::cout << foo("ABACAB") << std::endl;
    std::cout << foo("ABCDEDQZC") << std::endl;

    return 0;
}
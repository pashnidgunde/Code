#pragma once

#include <map>

namespace pn
{
    namespace algo
    {
        template<typename Iter, typename Op>
        void coutingSort(Iter begin, Iter end, Op op)
        {
            // can't be unordered because we need the order 
            // either aschending or descendin`g
            std::map<int,int> countOfElements;
            while (begin < end)
            {
               auto prev = countOfElements[*begin];
               prev++;
               countOfElements[*begin] = prev;
            }
        }
    }
}
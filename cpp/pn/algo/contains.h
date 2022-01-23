#ifndef PN_ALGORITHM_CONTAINS_HPP
#define PN_ALGORITHM_CONTAINS_HPP

#include <utility>
#include <algorithm>

namespace pn
{
    namespace algorithm
    {
        template<typename Iter>
        std::pair<bool,size_t> contains_in_order(Iter begin1,Iter end1,Iter begin2, Iter end2)
        {
            auto search_iter = begin1;
            auto substring_iter = begin2;
            auto count = 0;
            auto index = -1;
            while(search_iter != end1 && substring_iter != end2)
            {
                if (*substring_iter == *search_iter)
                {
                    count++;
                    if (substring_iter == begin2) 
                    {
                        index = std::distance(begin1,search_iter);
                    }
                    substring_iter++;
                }
                else
                {
                    count=0;
                    substring_iter = begin2;
                }
                search_iter++;
            }

            return std::make_pair((count == std::distance(begin2,end2)),index);
        }
    }
}

#endif
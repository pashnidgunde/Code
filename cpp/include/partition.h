#pragma once

#include "swap.h"

namespace pn
{
    namespace algo
    {
        // Partition element considering pivot as last element
        template<typename Iter, typename Op>
        Iter partition(Iter begin, Iter end, Op op) {
            Iter pivot = begin - 1;
            Iter iter = begin;
            while (iter < end) {
                if (op(*iter , *end)) {
                    pivot = pivot + 1;
                    pn::algo::swap(*pivot, *iter);
                }
                std::advance(iter,1);
            }
            std::advance(iter,1);
            pn::algo::swap(*iter, *end);
            return pivot + 1;
        }
    }
}
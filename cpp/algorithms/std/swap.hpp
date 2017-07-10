// Implement version of std::swap

#ifndef __SWAP_HPP__
#define __SWAP_HPP__

namespace pn
{
    namespace algo
    {
        template < class T>
        void swap ( T& l, T& r)
        {
            auto t = std::move(l);
            l = std::move(r);
            r = std::move(t);
        }
    }
}

#endif

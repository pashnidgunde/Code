#include <iostream>


namespace pn
{
    namespace index_sequence
    {
        template<typename T,size_t size>
        struct make_integer_sequence
        {

        };
    }
}






int main()
{
    using type = pn::index_sequence::make_integer_sequence<int,5>;
    return 0;
}
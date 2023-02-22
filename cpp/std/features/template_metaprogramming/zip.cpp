#include <type_traits>

template<int ...>
struct Vector;

template<typename ...>
struct zip;

template<int ...args>
struct zip<Vector<args...>>
{
    using type = Vector<args...>;
};


template<int ...lhs, int ...rhs, typename ...rest>
struct zip<Vector<lhs...>, Vector<rhs...>, rest ...>
{
    using type = zip<Vector<(lhs * rhs)...>, rest...>::type;
};


static_assert(std::is_same_v<zip<Vector<2, 4, 6>, 
                               Vector<1, 2, 3>, 
                               Vector<3, 6, 9>>::type, 
                               /* == */ Vector<6, 48, 162>>);

    //zip<V<2,4,6>,V<1,2,3>, V<3,6,9>>
    //zip<V<2,8,18>,V<3,6,9>>
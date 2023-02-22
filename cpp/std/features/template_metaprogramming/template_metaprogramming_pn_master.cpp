#include <cassert>
#include <tuple>

template<typename T, typename ...types>
struct contains_type : std::false_type {};
    
template<typename T, typename ...types>
struct contains_type<T,std::tuple<types...>>
{
    template<std::size_t index, typename T1, typename ...types1>
    static constexpr bool has_type()
    {
        using tuple_type = typename std::tuple<types1...>;
        if constexpr(index == std::tuple_size_v<tuple_type>)
            return false;
        else if constexpr (std::is_same_v<T1,typename std::tuple_element_t<index,tuple_type>>)
            return true;
        else
            return has_type<index+1,T1,types...>();
    }
    static constexpr bool value = has_type<0, T,types...>();
    
};

static constexpr bool value  = contains_type<double,std::tuple<double,int,char>>::value;

static_assert(contains_type<double,std::tuple<double,int,char>>::value);
static_assert(contains_type<int,std::tuple<double,int,char>>::value);
static_assert(contains_type<char,std::tuple<double,int,char>>::value);
static_assert(!contains_type<float,std::tuple<double,int,char>>::value);
static_assert(!contains_type<float,std::tuple<>>::value);












int main()
{
    
    return 0;
}
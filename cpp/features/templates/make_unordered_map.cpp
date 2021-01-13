#include <iostream>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <type_traits>

//-----------------------------------------------
// For N Args Begin
//----------------------------------------------
// this is required for generalizatoin
 template<typename,typename>
 struct ForNArgsImpl;

// specialization of above generalization
 template<std::size_t...NCalls, std::size_t...NArgs>
 // Fnctioncall indexes : {0,1}
 // Parameter Indexes : {0,1,2,3}
 // Expected get<{0+0}>args..,args<{0+1}>args..., ....
 struct ForNArgsImpl<std::index_sequence<NCalls...>,std::index_sequence<NArgs...>>
 {
    template<typename Callable, typename... Args>
    static void exec(Callable callable, const std::tuple<Args...>& args)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        constexpr auto count_of_function_calls = sizeof...(NCalls); //2
        using swallow = bool[];
        (void) swallow
        {
            (execN<NCalls * count_of_function_calls>(callable,args),true)...
            // execN<0*2>(callable,args)
            // exec(1*2)(callable,args)
        };
    }

    template<std::size_t Base, typename Callable, typename... Args>
    // Base (0,2)
    // Nargs(0,1)
    // Args (1,2,3,4)
    static void execN(Callable callable, const std::tuple<Args...>& args)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        callable(std::get<Base+NArgs>(args)...);
        // callable(std::get<0+0>(args);
        // callable(std::get<0+1>(args);
        // callable(std::get<1+1>(args);
        // callable(std::get<1+2>(args);
    }
 };

// size_t, size_t compiler fails to compile this
//template<typename Callable, size_t groupsize, typename ... Args>
//forNArgs(callable,2,1,2,3,3);
// hence lets rearrange
template<size_t GroupSize,typename Callable, typename ... Args>
void forNArgs(Callable fn, Args ...args)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //note constexpr so that it can be deduced at compile time
    constexpr auto number_of_arguments = sizeof...(Args);
    static_assert(number_of_arguments % GroupSize == 0,"Args must be in multiple of group size");

    // how many function calls do we need ? => number of args / group size
    constexpr auto number_of_func_calls = number_of_arguments / GroupSize;
    using FunctionCallIndexes = std::make_index_sequence<number_of_func_calls>;
    // For args {1,2,3,4} and group size = 2 ==> {0,1}

    // how many parameters do we need to pass to callable ? => Groupsize
    using ParameterIndexes = std::make_index_sequence<GroupSize>;
    // => {0,1}
        
    ForNArgsImpl<FunctionCallIndexes,ParameterIndexes>::exec
    (
        fn,
        // Forward the passed arguments as an `std::tuple`.
        std::forward_as_tuple(args...)
    );
};
//-----------------------------------------------------------------------------
// For N Args Ends
//------------------------------------------------------------------------------
template <typename Arg, typename... Args>
void doPrint(std::ostream& out, Arg&& arg, Args&&... args)
{
    out << std::forward<Arg>(arg);
    using expander = int[];
    (void)expander{0, (void(out << ',' << std::forward<Args>(args)), 0)...};
}

template<typename IndexSeqT,typename...Args>
struct KVHelper;

// accepts index_sequence and all variadic args
template<std::size_t... IndexSeqT, typename ...Args>
struct KVHelper<std::index_sequence<IndexSeqT...>, Args...>
{
    static_assert
    (
        sizeof...(Args)%2 == 0, 
        "Must in mutiples of 2"
    );
    
    static_assert
    (
        // {0,1}
        sizeof...(IndexSeqT) == sizeof...(Args) / 2, 
        //{1,2,3,4}
        "Size of index sequences must be half of size of args"
    );

    template<std::size_t TI>
    using TypeAt = std::tuple_element_t<TI,std::tuple<Args...>>;

    using KeyType = std::common_type_t<TypeAt<IndexSeqT *2>...>;
    // using KeyType = std::common_type_t
    // < 
    //    TypeAt<0*2>,
    //    TypeAt<1*2>
    //    TypeAt<2*2>
    // >

    using ValueType = std::common_type_t<TypeAt<(IndexSeqT *2) + 1>...>;
    // using ValueType = std::common_type_t
    // < 
    //    TypeAt<0*2 + 1>,
    //    TypeAt<1*2 + 1>
    //    TypeAt<2*2 + 1>
    // >

};

template<typename... Args>
using HelperFor = KVHelper
<
    // Index sequences must be half of args
    // K V K V
    // 0 1 2 3
    // index sequence {0,1}
    std::make_index_sequence<sizeof...(Args) / 2>, 
    Args...
>;

template<typename... Args>
using CommonKeyType = typename HelperFor<Args...>::KeyType;

template<typename... Args>
using CommonValueType = typename HelperFor<Args...>::ValueType;

static_assert
(
    std::is_same
    <
        CommonKeyType<std::string,int>,
        std::string
    >(),
    "Type must be std::string"
);

static_assert
(
    std::is_same
    <
        CommonValueType<std::string,int>,
        int
    >(),
    "Type must be std::integer"
);

static_assert
(
    std::is_same
    <
        CommonKeyType
        <
            std::string, int,
            std::string, int,
            const char*, int
        >,
        std::string
    >(),
    "Must be std::string"
);

// 1,2,3,4
template<typename ...Args>
auto make_unordered_map(Args&& ... args)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // (types) K V K V K V 
    // (K seq) 0   2   4 
    // (V seq)   1   3   5

    using KeyType = CommonKeyType<Args...>;
    using ValueType = CommonValueType<Args...>;
    
    std::unordered_map<KeyType,ValueType> result;
    result.reserve(sizeof...(Args) / 2);
    
    auto callable = [&result](const&& key, const&& value)
    {
        result.emplace(
            std::forward<decltype(key)>(key), 
            std::forward<decltype(value)>(value)
        );
    };

    forNArgs<2>(callable,std::forward<Args>(args)...);
    
    return result;
}


int main()
{
    auto my_map = make_unordered_map(1,2,3,4);
    for (auto&n : my_map)
    {
        std::cout << n.first << n.second << std::endl;
    }
    
    // //using namespace std::literals;
    // auto m 
    //     = make_unordered_map(
    //         "Hello", 1,
    //         "World", 2.f);

    // for (auto&elem : m)
    // {
    //     std::cout << elem.first << elem.second << std::endl;
    // }
    
    return 0;
}
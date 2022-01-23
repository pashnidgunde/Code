// youtube : dive into c++14 2

#include <iostream>
#include <type_traits>
#include <utility>
#include <tuple>


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
    static void exec(Callable&& callable, std::tuple<Args...>&& args)
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
    static void execN(Callable&& callable, const std::tuple<Args...>& args)
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
void forNArgs(Callable&& fn, Args&& ...args)
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

int main()
{
    auto callable = [](auto& arg1, auto& arg2) { std::cout << arg1 + arg2 << std::endl;};
    forNArgs<2>(callable,1,2,3,3); // 3,6
    auto callable1 = [](auto& arg1, auto& arg2, auto arg3) { std::cout << arg1 + arg2 + arg3 << std::endl;};
    forNArgs<3>(callable1,1,2,3,1,2,3); // 6,6
    return 0;
}
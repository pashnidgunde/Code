#include <type_traits>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <list>

template<typename T>
struct is_pointer
{
    static constexpr bool value = false;
};

template<typename T>
struct is_pointer<T*>
{
    static constexpr bool value = true;
};

template<typename T>
struct strip_pointer
{
    using type = T;
};

template<typename T>
struct strip_pointer<T*>
{
    using type = T;
};


template<typename T>
void print(T a)
{
    using TWithoutPointer = typename strip_pointer<T>::type;
    if constexpr(is_pointer<T>::value && std::is_floating_point<TWithoutPointer>::value)
    {
        std::cout << *a << " , " << std::endl; 
    }
    else
    {
        std::cout << a << " , " << std::endl; 
    }
}

template<typename T1,typename T2, typename T3>
void print(T1 a, T2 b, T3 c)
{
    print(a);
    print(b);
    print(c);
}

template<typename T, typename U>
struct Map
{
    using Key = T;
    using Value = U;
    Map() { std::cout << "Default map \n"; }
};

template<typename U>
struct Map<int,U>
{
    Map() { std::cout << "partial specialization \n"; }
};

template<>
struct Map<int,int>
{
    Map() { std::cout << "Full Specialization \n"; }
};

template<bool, typename T, typename F>
struct if_;

template<typename T, typename F>
struct if_<true,T,F>
{
    using type = T;
};

template<typename T, typename F>
struct if_<false,T,F>
{
    using type = F;
};

struct true_type
{
    static constexpr bool value = true;
};

struct false_type
{
    static constexpr bool value = false;
};


bool contains(std::vector<std::string> values, std::string find, int index )
{
    if (values[index] == find) return true;
    if (index == values.size()) return false;
    return contains(values,find, index+1);
}

template<typename SEARCH, typename TUPLE, size_t INDEX = 0>
struct contains_type : 
    if_ <std::is_same<std::tuple_element_t<INDEX, TUPLE>,SEARCH>::value,
            std::true_type,
            typename if_<(std::tuple_size<TUPLE>::value - 1 == INDEX),
                std::false_type,
                contains_type<SEARCH,TUPLE,INDEX+1>
            >::type
        >::type
{
    
};

template<typename SEARCH>
struct contains_type<SEARCH,std::tuple<>, 0> : std::false_type {};

// zero arg printn
void printn()
{
}

template<typename Last>
void printn(Last&& e)
{
    std::cout << e << std::endl;
}

template<typename T0, typename... T1toN>
void printn(T0&& t, T1toN&&... rest)
{
    std::cout << std::forward<T0>(t) << std::endl;
    printn(std::forward<T1toN>(rest)...);
}


template<typename TUPLE, std::size_t ...I>
// tag dispatch, note std::index_sequence has no variable, here for for compiler to use this override
void print_tuple_impl(TUPLE&& t, std::index_sequence<I...>)
{
    printn(std::get<I>(std::forward<TUPLE>(t))...);
    // parameter pack
    //evaluates to printn(std::get<0>(t), std::get<1>(t),....)
}

template<typename TUPLE>
void print_tuple(TUPLE&& t)
{
    std::cout << "In Print Tuple: " << std::endl;
    constexpr size_t tuple_size = std::tuple_size<typename std::remove_reference<TUPLE>::type>::value;
    print_tuple_impl(std::forward<TUPLE>(t),std::make_index_sequence<tuple_size>{});
}


namespace ct
{
    bool contains_type_fn(const std::string& SEARCH, std::list<std::string> types)
    {
        if (types.empty()) return false;
        if (SEARCH == types.front()) return true;
        types.pop_front();
        return contains_type_fn(SEARCH, types);
    }

    template<typename ...>
    struct type_list {};

    template<typename LIST>
    struct empty : public std::false_type {};

    template<>
    struct empty<type_list<>> : public std::true_type {};
    static_assert (empty<type_list<>>::value);
    static_assert (empty<type_list<float>>::value == false);

    template<typename LIST>
    struct front {};

    template<typename T0, typename ...T1toN>
    struct front<type_list<T0, T1toN...>>
    {
        using type = T0;
    };
    static_assert(std::is_same_v<front<type_list<int,bool>>::type,int>);

    template<typename LIST>
    struct pop_front;

    template<typename T0, typename ...T1toN>
    struct pop_front<type_list<T0,T1toN...>>
    {
        using type = type_list<T1toN...>;
    };
    static_assert(std::is_same_v<pop_front<type_list<int,bool>>::type,type_list<bool>>);

    template<typename LIST>
    using front_t = typename front<LIST>::type;

    template<typename LIST>
    using pop_front_t = typename pop_front<LIST>::type;

    template<typename LIST>
    static constexpr bool empty_v = empty<LIST>::value;

    template<typename SEARCH, typename LIST>
    struct non_empty_contains_type;
    
    template<typename SEARCH, typename LIST>
    struct contains_type : 
        if_<
            empty_v<LIST>,
            std::false_type,
            non_empty_contains_type<SEARCH,LIST>
        >::type
    {};

    template<typename SEARCH, typename LIST>
    struct non_empty_contains_type : 
        if_<std::is_same_v<front_t<LIST>,SEARCH>,
            std::true_type,
            contains_type<SEARCH,pop_front_t<LIST>>
        >::type
    {};
}

namespace mct
{
    template<typename SEARCH, typename LIST>
    struct modified_contains_type;

    template<typename SEARCH>
    struct modified_contains_type<SEARCH,ct::type_list<>> : false_type {}; 

    template<typename SEARCH, typename LIST>
    struct modified_contains_type : 
        if_<std::is_same_v<ct::front_t<LIST>,SEARCH>,
            std::true_type,
            modified_contains_type<SEARCH,ct::pop_front_t<LIST>>
        >::type
    {};
}

int main()
{
    {
        // template functions and metafunctions
        std::string hello = "Hello";
        print(hello, 1, 2.5);
        print(&hello,1,2.5);
        float x = 0;
        double y = 2.5;
        print(&hello,&x,&y);
    }

    {
        Map<int,int> m; // full specialization
        Map<int,double> m1; // partial 
        Map<double,std::string> m3; // template
    }
    
    {
        // compile time if
        static_assert(std::is_same<if_<(5==5), double, int>::type, double>::value);
        static_assert(std::is_same<if_<(5!=5), double, int>::type, int>::value);
    }

    {
        //contains_type implementation
        // step 1 : first write runtime equivalent without loops and recursion
        //std::cout << "\n" << contains(std::vector<std::string>{"int", "float", "double"}, "int", 0);
        // transform to compile time
        std::tuple<int,bool,float>t;
        static_assert(contains_type<double, decltype(t)>::value == false);
        static_assert(contains_type<char, decltype(t)>::value == false);    
        static_assert(contains_type<int, decltype(t)>::value == true);    
        static_assert(contains_type<int, std::tuple<>>::value == false);    
    }

    {
        // variadic templates
        printn("Hello",1, false, 2.0);
    }

    {
        auto t = std::make_tuple(10,false,10.00, 'c', "funny");
        print_tuple(t);
    }

    // metaprograming library contains_type ... how to 
    {
        std::cout << std::boolalpha << ct::contains_type_fn("bool", std::list<std::string> {"bool", "int", "double"});
        ct::type_list<int,bool,double> types;
        static_assert(ct::contains_type<int,decltype(types)>::value); 
        static_assert(ct::contains_type<char,decltype(types)>::value == false); 
    }

    // metaprogramming library contains_type modified version
    {
        std::cout << std::boolalpha << ct::contains_type_fn("bool", std::list<std::string> {"bool", "int", "double"});
        ct::type_list<int,bool,double> types;
        static_assert(mct::modified_contains_type<int,decltype(types)>::value); 
        static_assert(mct::modified_contains_type<char,decltype(types)>::value == false); 
    }
    
    return 0;
    
    
}
template<int N>
struct abs
{
    //static_assert(N != INT_MIN)
    static const int value = (N<0) ? -N : N;
};

template<typename T>
struct type_is
{
    using type = T;
};

//---------------------------------------------------------
template<typename T>
struct remove_volatile : public type_is<T>
{    
};

template<typename T>
struct remove_volatile<T volatile>
{
    using type = T;
};
//---------------------------------------------------------

template<typename T>
struct remove_const : public type_is<T> {};

template<typename T>
struct remove_const<T const> { using type = T; };

template<typename T>
using remove_cv = remove_volatile<remove_const<T>::type> {};
//---------------------------------------------------------

// named as std::conditional
template<bool, typename T, typename F>
struct IF : public is_type<T> {};

template<typename T, typename F>
struct IF<false,T,F> { using type = F; };
//---------------------------------------------------------

template<bool,typename T> 
struct enable_if : public type_is<T> { type = T; };
template<bool,typename T> 
struct enable_if : public type_is<false,T> { };
//---------------------------------------------------------

template<typename T, T v>
struct integral_constant
{
    using type = T;
    T value = v;
};

template <bool b> 
struct conditional : public integral_constant<bool,b>
{
};

using true_type = conditional<true>;
using false_type = conditional<false>;

template<typename T> 
struct is_void : public false_type {};

template <> 
struct is_void<void> : public true_type {};

template <> 
struct is_void<void const> : public true_type {};

template<typename T, typename U>
struct is_same : public false_type{};

template<typename T>
struct is_same<T,T> : public true_type{};

//------------------------------
template<typename T, typename... Types>
struct is_one_of;

template<typename T>
struct is_one_of<T> : false_type {};

template<typename T, typename ... P1ToN>
struct is_one_of<T,T,P1ToN...> : true_type {};

template<typename T, typename P0, typename ... P1ToN>
struct is_one_of<T,P0,P1ToN...> : is_one_of<T,P1ToN...>{};

template<typename T>
using is_void = is_one_of<T, void, void const, void volatile, void const volatile>;

// specialization / more specialized

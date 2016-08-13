#ifndef MINIASCAPE_MAKE_ARRAY
#define MINIASCAPE_MAKE_ARRAY
#include <array>

namespace miniascape
{

template<typename T_term, typename... T_args>
struct is_all_convertible;

template<typename T_term, typename T_head, typename... T_args>
struct is_all_convertible<T_term, T_head, T_args...>
{
    constexpr static bool value = std::is_convertible<T_term, T_head>::value &&
        is_all_convertible<T_term, T_args...>::value;
};

template<typename T_term, typename T_tail>
struct is_all_convertible<T_term, T_tail>
{
    constexpr static bool value = std::is_convertible<T_term, T_tail>::value;
};

template<typename... T_args>
struct is_all_same;

template<typename T_head, typename T_body, typename... T_args>
struct is_all_same<T_head, T_body, T_args...>
{
    constexpr static bool value = std::is_same<T_head, T_body>::value &&
        is_all_same<T_body, T_args...>::value;
};

template<typename T_head, typename T_tail>
struct is_all_same<T_head, T_tail>
{
    constexpr static bool value = std::is_same<T_head, T_tail>::value;
};

template<typename T_head>
struct is_all_same<T_head>
{
    constexpr static bool value = true;
};

template<typename... T_args>
struct head_type;

template<typename T_head, typename... T_args>
struct head_type<T_head, T_args...>
{
    typedef T_head type;
};

template<typename T_head>
struct head_type<T_head>
{
    typedef T_head type;
};

template<typename T, typename... T_args>
inline std::array<T, sizeof...(T_args)> make_array_type(const T_args& ... args)
{
    static_assert(is_all_convertible<T, T_args...>::value, "not convertible");
    return std::array<T, sizeof...(T_args)>{{args...}};
}

template<typename... T_args>
inline std::array<typename head_type<T_args...>::type, sizeof...(T_args)>
make_array(const T_args& ... args)
{
    static_assert(is_all_same<T_args...>::value, "not convertible");
    return std::array<typename head_type<T_args...>::type, sizeof...(T_args)>{
        {args...}
    };
}

}//miniascape

#endif /* MINIASCAPE_MAKE_ARRAY */

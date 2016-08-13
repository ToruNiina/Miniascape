#ifndef MINIASCAPE_MAKE_ARRAY
#define MINIASCAPE_MAKE_ARRAY
#include "util/meta_funcs.hpp"
#include <array>

namespace miniascape
{

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

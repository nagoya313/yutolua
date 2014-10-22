#ifndef YUTOLUA_DETAIL_RESULT_SIZE_HPP_
#define YUTOLUA_DETAIL_RESULT_SIZE_HPP_
#include <type_traits>

namespace yutolua { namespace detail {
template <typename Result>
struct result_size : std::integral_constant<int, 1> {};

template <>
struct result_size<void> : std::integral_constant<int, 0> {};
}}

#endif
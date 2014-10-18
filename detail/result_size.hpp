#ifndef YUTOLUA_DETAIL_RESULT_SIZE_HPP_
#define YUTOLUA_DETAIL_RESULT_SIZE_HPP_
#include <array>
#include <tuple>
#include <utility>

namespace yutolua { namespace detail {
template <typename Result>
struct result_size {
  static const int value = 1;
};

template <>
struct result_size<void> {
  static const int value = 0;
};

template <typename First, typename Second>
struct result_size<std::pair<First, Second>> {
  static const int value = 2;
};

template <typename V, std::size_t N>
struct result_size<std::array<V, N>> {
  static const int value = N;
};

template <typename... Values>
struct result_size<std::tuple<Values...>> {
  static const int value = std::tuple_size<std::tuple<Values...>>::value;
};
}}

#endif
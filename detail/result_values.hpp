#ifndef YUTOLUA_DETAIL_RESULT_VALUES_HPP_
#define YUTOLUA_DETAIL_RESULT_VALUES_HPP_
#include <array>
#include <tuple>
#include <utility>
#include "auto_pop.hpp"
#include "convert.hpp"

namespace yutolua { namespace detail {
template <typename Result>
struct result_values {
  Result operator ()(lua_State *lua) const {
    auto_pop<1> pop{lua};
    return convert<Result>(lua, -1);
  }
};

template <>
struct result_values<void> {
  void operator ()(lua_State *) const {}
};

template <typename First, typename Second>
struct result_values<std::pair<First, Second>> {
  std::pair<First, Second> operator ()(lua_State *lua) const {
    auto_pop<2> pop{lua};
    return {convert<First>(lua, -2), convert<Second>(lua, -1)};
  }
};

template <typename V, std::size_t N>
struct result_values<std::array<V, N>> {
  std::array<V, N> operator ()(lua_State *lua) const {
    auto_pop<N> pop{lua};
    std::array<V, N> array{};
    for (int i = 0; i < N; ++i) {
      array[i] = convert<V>(lua, -(static_cast<int>(N) - i));
    }
    return array;
  }
};

template <typename Tuple, int N, typename Value, typename... Values>
void set_result_tuple(lua_State *lua, Tuple &tuple) {
  std::get<N>(tuple) = convert<Value>(lua, -(static_cast<int>(std::tuple_size<Tuple>::value) - N));
  set_result_tuple<Tuple, N + 1, Values...>(lua, tuple);
}

template <typename Tuple, int>
void set_result_tuple(lua_State *, Tuple &) {}

template <typename... Values>
struct result_values<std::tuple<Values...>> {
  std::tuple<Values...> operator ()(lua_State *lua) const {
    auto_pop<std::tuple_size<std::tuple<Values...>>::value> pop{lua};
    std::tuple<Values...> tuple{};
    set_result_tuple<std::tuple<Values...>, 0, Values...>(lua, tuple);
    return tuple;
  }
};
}}

#endif
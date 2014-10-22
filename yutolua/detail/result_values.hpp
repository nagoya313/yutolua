#ifndef YUTOLUA_DETAIL_RESULT_VALUES_HPP_
#define YUTOLUA_DETAIL_RESULT_VALUES_HPP_
#include "auto_pop.hpp"
#include "get.hpp"

namespace yutolua { namespace detail {
template <typename Result>
struct result_values {
  Result operator ()(lua_State *lua) const {
    auto_pop<1> pop{lua};
    return get<Result>(lua, -1);
  }
};

template <>
struct result_values<void> {
  void operator ()(lua_State *) const {}
};
}}

#endif
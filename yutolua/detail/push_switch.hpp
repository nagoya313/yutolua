#ifndef YUTOLUA_DETAIL_PUSH_SWITCH_HPP_
#define YUTOLUA_DETAIL_PUSH_SWITCH_HPP_
#include "push.hpp"
#include "push_ref.hpp"

namespace yutolua { namespace detail {
template <typename T>
struct push_switch {
  void operator ()(lua_State *lua, T value) const {
    push<T>(lua, value);
  }
};

template <typename T>
struct push_switch<T &> {
  void operator ()(lua_State *lua, T &value) const {
    push_ref(lua, value);
  }
};

template <typename T>
struct push_switch<const T &> {
  void operator ()(lua_State *lua, const T &value) const {
    push<T>(lua, value);
  }
};
}}

#endif
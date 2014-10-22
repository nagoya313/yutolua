#ifndef YUTOLUA_DETAIL_ARGS_PUSH_HPP_
#define YUTOLUA_DETAIL_ARGS_PUSH_HPP_
#include <type_traits>
#include "push_switch.hpp"

namespace yutolua { namespace detail {
template <typename Arg, typename... Args>
inline void args_push(lua_State *lua, Arg arg, Args... args) {
  push_switch<Arg>{}(lua, std::forward<Arg>(arg));
  args_push<Args...>(lua, std::forward<Args>(args)...);
}

template <typename Arg>
inline void args_push(lua_State *lua, Arg arg) {
  push_switch<Arg>{}(lua, std::forward<Arg>(arg));
}

template <typename T = void>
inline T args_push(lua_State *) {}
}}

#endif
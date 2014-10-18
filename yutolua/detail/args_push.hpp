#ifndef YUTOLUA_DETAIL_ARGS_PUSH_HPP_
#define YUTOLUA_DETAIL_ARGS_PUSH_HPP_
#include "push.hpp"

namespace yutolua { namespace detail {
template <typename Arg, typename... Args>
void args_push(lua_State *lua, const Arg &arg, const Args &... args) {
  push(lua, arg);
  args_push(lua, args...);
}

template <typename Arg>
void args_push(lua_State *lua, const Arg &arg) {
  std::cout << &arg << std::endl;
  push(lua, arg);
}

inline
void args_push(lua_State *) {}
}}

#endif
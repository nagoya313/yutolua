#ifndef YUTOLUA_DETAIL_C_FUNCTION_HPP_
#define YUTOLUA_DETAIL_C_FUNCTION_HPP_
#include "c_function_call.hpp"
#include "push.hpp"

namespace yutolua { namespace detail {
template <typename>
class c_function;

template <typename Result, typename... Args>
struct c_function<Result (Args...)> {
  static int call(lua_State *lua) {
    const auto ptr = reinterpret_cast<void (*)(Args...)>(lua_touserdata(lua, lua_upvalueindex(1)));
    push<Result>(lua, c_function_call<void (*)(Args...), Args...>(lua, ptr));
    return 1;
  }
};

template <typename... Args>
struct c_function<void (Args...)> {
  static int call(lua_State *lua) {
    const auto ptr = reinterpret_cast<void (*)(Args...)>(lua_touserdata(lua, lua_upvalueindex(1)));
    c_function_call<void (*)(Args...), Args...>(lua, ptr);
    return 0;
  }
};
}}

#endif
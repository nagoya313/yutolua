#ifndef YUTOLUA_DETAIL_C_FUNCTION_CALL_HPP_
#define YUTOLUA_DETAIL_C_FUNCTION_CALL_HPP_
#include "arg_check.hpp"

namespace yutolua { namespace detail {
template <int N>
struct c_function_call_args {
  template <typename Func, typename Arg, typename... Args>
  static void call(lua_State *lua, Func f, const Args &... args) {
    c_function_call_args<N - 1>::template call<Func, Args...>(lua, f, arg_check<Arg>(lua, N), args...);
  }

  template <typename Func, typename Arg, typename... Args>
  static void call(lua_State *lua, Func f) {
    c_function_call_args<N - 1>::template call<Func, Args...>(lua, f, arg_check<Arg>(lua, N));
  }
};

template <>
struct c_function_call_args<1> {
  template <typename Func, typename Arg, typename... Args>
  static void call(lua_State *lua, Func f, const Args &... args) {
    f(arg_check<Arg>(lua, 1), args...);
  }

  template <typename Func, typename Arg>
  static void call(lua_State *lua, Func f) {
    f(arg_check<Arg>(lua, 1));
  }
};

template <>
struct c_function_call_args<0> {
  template <typename Func>
  static void call(lua_State *, Func f) {
    f();
  }
};

template <typename Func, typename... Args>
void c_function_call(lua_State *lua, Func f) {
  c_function_call_args<sizeof...(Args)>::template call<Func, Args...>(lua, f);
}
}}

#endif
#ifndef YUTOLUA_DETAIL_C_FUNCTION_CALL_HPP_
#define YUTOLUA_DETAIL_C_FUNCTION_CALL_HPP_
#include "arg_check.hpp"

namespace yutolua { namespace detail {
template <int Cur, int Size, bool End, typename... Args>
struct c_function_call_impl {
  template <typename Result, typename Arg, typename... Args2, typename... Args3>
  static Result call(lua_State *lua, Result (*f)(Args...), Args3... args) {
    return c_function_call_impl<Cur + 1, Size, (Cur + 1 == Size), Args...>::template call<Result, Args2...>(lua, f, args..., arg_check<Arg>(lua, Cur));
  }

  template <typename Result, typename Arg, typename... Args2>
  static Result call(lua_State *lua, Result (*f)(Args...)) {
    return c_function_call_impl<Cur + 1, Size, (Cur + 1 == Size), Args...>::template call<Result, Args2...>(lua, f, arg_check<Arg>(lua, Cur));
  }
};

template <int Cur, int Size, typename... Args>
struct c_function_call_impl<Cur, Size, true, Args...> {
  template <typename Result, typename Arg, typename... Args2, typename... Args3>
  static Result call(lua_State *lua, Result (*f)(Args...), Args3... args) {
    return f(args..., arg_check<Arg>(lua, Cur));
  }

  template <typename Result, typename Arg>
  static Result call(lua_State *lua, Result (*f)(Arg)) {
    return f(arg_check<Arg>(lua, Cur));
  }
};

template <typename... Args>
struct c_function_call_impl<1, 0, false, Args...> {
  template <typename Result>
  static Result call(lua_State *lua, Result (*f)()) {
    return f();
  }
};

template <typename Result, typename... Args>
Result c_function_call(lua_State *lua, Result (*f)(Args...)) {
  return c_function_call_impl<1, sizeof...(Args), (1 == sizeof...(Args)), Args...>::template call<Result, Args...>(lua, f);
}
}}

#endif
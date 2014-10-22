#ifndef YUTOLUA_DETAIL_FUNCTION_CALL_HPP_
#define YUTOLUA_DETAIL_FUNCTION_CALL_HPP_
#include <functional>
#include <typeinfo>
#include <boost/utility/string_ref.hpp>
#include "arg_check.hpp"
#include "push.hpp"
#include "result_size.hpp"

namespace yutolua { namespace detail {
template <typename Function, int Cur, int Size, bool End, typename... Args>
struct function_call_impl;

template <typename Function, int Cur, int End, typename... Args>
using function_call_impl_t = function_call_impl<Function, Cur, End, Cur == End, Args...>;

template <typename Function, int Cur, int Size, bool End, typename... Args>
struct function_call_impl {
  template <typename Result, typename Arg, typename... Args2, typename... Args3>
  static Result call(lua_State *lua, Function f, Args3... args) {
    return function_call_impl_t<Function, Cur + 1, Size, Args...>::template call<Result, Args2...>(lua, f, args..., arg_check<Arg>(lua, Cur));
  }

  template <typename Result, typename Arg, typename... Args2>
  static Result call(lua_State *lua, Function f) {
    return function_call_impl_t<Function, Cur + 1, Size, Args...>::template call<Result, Args2...>(lua, f, arg_check<Arg>(lua, Cur));
  }
};

template <typename Function, int Cur, int Size, typename... Args>
struct function_call_impl<Function, Cur, Size, true, Args...> {
  template <typename Result, typename Arg, typename... Args2, typename... Args3>
  static Result call(lua_State *lua, Function f, Args3... args) {
    return f(args..., arg_check<Arg>(lua, Cur));
  }

  template <typename Result, typename Arg>
  static Result call(lua_State *lua, Function f) {
    return f(arg_check<Arg>(lua, Cur));
  }
};

template <typename Function, typename... Args>
struct function_call_impl<Function, 1, 0, false, Args...> {
  template <typename Result>
  static Result call(lua_State *, Function f) {
    return f();
  }
};

template <typename Result, typename... Args>
struct function_call_switch {
  template <typename Function>
  void operator ()(lua_State *lua, Function F) const {
    auto ret = function_call_impl_t<Function, 1, sizeof...(Args), Args...>::template call<Result, Args...>(lua, f);
    push<Result>(lua, ret);
  }
};

template <typename... Args>
struct function_call_switch<void, Args...> {
  template <typename Function>
  void operator ()(lua_State *lua, Function f) const {
    function_call_impl_t<Function, 1, sizeof...(Args), Args...>::template call<void, Args...>(lua, f);
  }
};

template <typename Result, typename... Args>
inline int c_function_call(lua_State *lua) {
  const auto ptr = reinterpret_cast<Result (*)(Args...)>(lua_tocfunction(lua, lua_upvalueindex(1)));
  function_call_switch<Result, Args...>{}(lua, ptr);
  return result_size<Result>::value;
}

template <typename Result, typename... Args>
int cpp_function_call(lua_State *lua) {
  using Function = std::function<Result (Args...)>;
  auto function = static_cast<Function **>(luaL_checkudata(lua, 1, lua_tostring(lua, lua_upvalueindex(1))));
  function_call_switch<Result, Args...>{}(lua, **function);
  return result_size<Result>::value;
}

template <typename Function>
int cpp_function_delete(lua_State *lua) {
  auto c = static_cast<Function **>(luaL_checkudata(lua, 1, lua_tostring(lua, lua_upvalueindex(1))));
  delete *c;
  return 0;
}

template <typename Result, typename... Args>
inline void cpp_function_new(lua_State *lua, std::function<Result (Args...)> func) {
  using Function = std::function<Result (Args...)>;
  auto new_func = static_cast<Function **>(lua_newuserdata(lua, sizeof(Function *)));
  *new_func = new Function{func};
  const std::string table_name = std::string("yutolua.") + typeid(Function).name();
  if (luaL_newmetatable(lua, table_name.c_str())) {
    lua_pushfstring(lua, table_name.c_str());
    lua_pushcclosure(lua, cpp_function_call<Result, Args...>, 1);
    lua_setfield(lua, -2, "__call");
    lua_pushfstring(lua, table_name.c_str());
    lua_pushcclosure(lua, cpp_function_delete<Function>, 1);
    lua_setfield(lua, -2, "__gc");
  }
  lua_setmetatable(lua, -2);
}
}}

#endif
#ifndef YUTOLUA_DETAIL_C_FUNCTION_HPP_
#define YUTOLUA_DETAIL_C_FUNCTION_HPP_
#include "c_function_call.hpp"
#include "result_size.hpp"

namespace yutolua { namespace detail {
template <typename>
class c_function;

template <typename Result, typename... Args>
struct c_function<Result (Args...)> {
  static int call(lua_State *lua) {
    const auto ptr = reinterpret_cast<Result (*)(Args...)>(lua_tocfunction(lua, lua_upvalueindex(1)));
    c_function_call<Result, Args...>(lua, ptr);
    return result_size<Result>::value;
  }
};
}}

#endif
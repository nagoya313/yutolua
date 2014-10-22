#ifndef YUTOLUA_DETAIL_ARG_CHECK_HPP_
#define YUTOLUA_DETAIL_ARG_CHECK_HPP_
#include <string>
#include <type_traits>
#include "type_check.hpp"

namespace yutolua { namespace detail {
template <typename T, match_bool<T> *& = enabler>
inline bool arg_check(lua_State *lua, int index) {
  return lua_toboolean(lua, index) != 0;
}

template <typename T, match_signed_integral<T> *& = enabler>
inline lua_Integer arg_check(lua_State *lua, int index) {
  return luaL_checkinteger(lua, index);
}

template <typename T, match_unsigned_integral<T> *& = enabler>
inline lua_Unsigned arg_check(lua_State *lua, int index) {
  return luaL_checkunsigned(lua, index);
}

template <typename T, match_floating_point<T> *& = enabler>
inline lua_Number arg_check(lua_State *lua, int index) {
  return luaL_checknumber(lua, index);
}

template <typename T, match_c_string<T> *& = enabler>
inline const char *arg_check(lua_State *lua, int index) {
  return luaL_checkstring(lua, index);
}

template <typename T, match_arg_string<T> *& = enabler>
inline std::string arg_check(lua_State *lua, int index) {
  return luaL_checkstring(lua, index);
}
}}

#endif
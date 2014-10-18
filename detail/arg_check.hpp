#ifndef YUTOLUA_DETAIL_ARG_CHECK_HPP_
#define YUTOLUA_DETAIL_ARG_CHECK_HPP_
#include <string>
#include <type_traits>
#include "type_check.hpp"

namespace yutolua { namespace detail {
extern void *enabler;

template <typename T, typename std::enable_if<std::is_same<T, bool>::value>::type *& = enabler>
bool arg_check(lua_State *lua, int index) {
  return luaL_checkinteger(lua, index) != 0; // luaL_checkboolean???
}

template <typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value>::type *& = enabler>
T arg_check(lua_State *lua, int index) {
  return luaL_checkinteger(lua, index);
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value && !boost::is_same<T, bool>::value>::type *& = enabler>
T arg_check(lua_State *lua, int index) {
  return luaL_checkunsigned(lua, index);
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *& = enabler>
T arg_check(lua_State *lua, int index) {
  return luaL_checknumber(lua, index);
}

template <typename T, typename std::enable_if<std::is_same<T, std::string>::value || std::is_same<T, const std::string &>::value>::type *& = enabler>
std::string arg_check(lua_State *lua, int index) {
  return luaL_checkstring(lua, index);
}
}}

#endif
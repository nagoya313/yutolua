#ifndef YUTOLUA_DETAIL_PUSH_HPP_
#define YUTOLUA_DETAIL_PUSH_HPP_
#include <string>
#include <type_traits>

namespace yutolua { namespace detail {
extern void *enabler;

template <typename T, typename std::enable_if<std::is_same<T, bool>::value>::type *& = enabler>
void push(lua_State *lua, bool value) {
  lua_pushboolean(lua, value);
}

template <typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value>::type *& = enabler>
void push(lua_State *lua, T value) {
  lua_pushinteger(lua, value);
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value && !boost::is_same<T, bool>::value>::type *& = enabler>
void push(lua_State *lua, T value) {
  lua_pushunsigned(lua, value);
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *& = enabler>
void push(lua_State *lua, T value) {
  lua_pushnumber(lua, value);
}

template <typename T, typename std::enable_if<std::is_same<T, std::string>::value>::type *& = enabler>
void push(lua_State *lua, const std::string &value) {
  lua_pushlstring(vm, value.data(), value.size());
}
}}

#endif
#ifndef YUTOLUA_DETAIL_PUSH_HPP_
#define YUTOLUA_DETAIL_PUSH_HPP_
#include <cstddef>
#include <string>
#include "type_check.hpp"

namespace yutolua { namespace detail {
template <typename T = void>
inline void push(lua_State *lua) {}

template <typename T, match_nil<T> *& = enabler>
inline void push(lua_State *lua, std::nullptr_t) {
  lua_pushnil(lua);
}

template <typename T, match_bool<T> *& = enabler>
inline void push(lua_State *lua, bool value) {
  lua_pushboolean(lua, value);
}

template <typename T, match_signed_integral<T> *& = enabler>
inline void push(lua_State *lua, lua_Integer value) {
  lua_pushinteger(lua, value);
}

template <typename T, match_unsigned_integral<T> *& = enabler>
inline void push(lua_State *lua, lua_Unsigned value) {
  lua_pushinteger(lua, value);
}

template <typename T, match_floating_point<T> *& = enabler>
inline void push(lua_State *lua, lua_Number value) {
  lua_pushnumber(lua, value);
}

template <typename T, match_c_string<T> *& = enabler>
inline void push(lua_State *lua, const char *value) {
  lua_pushstring(lua, value);
}

template <typename T, match_string<T> *& = enabler>
inline void push(lua_State *lua, const std::string &value) {
  lua_pushlstring(lua, value.data(), value.size());
}
}}

#endif
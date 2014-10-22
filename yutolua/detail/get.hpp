#ifndef YUTOLUA_DETAIL_GET_HPP_
#define YUTOLUA_DETAIL_GET_HPP_
#include <string>
#include "type_check.hpp"

namespace yutolua { namespace detail {
template <typename T, match_bool<T> *& = enabler>
inline bool get(lua_State *lua, int index) {
  if (!lua_isboolean(lua, index)) {
    throw bad_cast{} << type_info{"value should be a boolean."};
  }
  return lua_toboolean(lua, index) != 0;
}

template <typename T, match_signed_integral<T> *& = enabler>
inline lua_Integer get(lua_State *lua, int index) {
  if (!lua_isnumber(lua, index)) {
    throw bad_cast{} << type_info{"value should be a number."};
  }
  return lua_tointeger(lua, index);
}

template <typename T, match_unsigned_integral<T> *& = enabler>
inline lua_Unsigned get(lua_State *lua, int index) {
  if (!lua_isnumber(lua, index)) {
    throw bad_cast{} << type_info{"value should be a number."};
  }
  return lua_tounsigned(lua, index);
}

template <typename T, match_floating_point<T> *& = enabler>
inline lua_Number get(lua_State *lua, int index) {
  if (!lua_isnumber(lua, index)) {
    throw bad_cast{} << type_info{"value should be a number."};
  }
  return lua_tonumber(lua, index);
}

template <typename T, match_string<T> *& = enabler>
inline std::string get(lua_State *lua, int index) {
  if (!lua_isstring(lua, index)) {
    throw bad_cast{} << type_info{"value should be a string."};
  }
  return lua_tostring(lua, index);
}
}}

#endif
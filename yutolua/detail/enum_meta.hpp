#ifndef YUTOLUA_DETAIL_ENUM_META_HPP_
#define YUTOLUA_DETAIL_ENUM_META_HPP_

namespace yutolua { namespace detail {
inline
int enum_not_find_error(lua_State *lua) {
  lua_pushstring(lua, "Not found enum member.");
  return lua_error(lua);
}

inline
int enum_assign_error(lua_State *lua) {
  lua_pushstring(lua, "Enum is read only.");
  return lua_error(lua);
}
}}

#endif
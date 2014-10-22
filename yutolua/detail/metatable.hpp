#ifndef YUTOLUA_DETAIL_METATABLE_HPP_
#define YUTOLUA_DETAIL_METATABLE_HPP_
#include "arg_check.hpp"
#include "push.hpp"

namespace yutolua { namespace detail {
inline int reference_error(lua_State *lua) {
  return luaL_error(lua, "Reference error.");
}

template <typename T>
inline void new_trivially_copyable_class_reference(lua_State *lua, const char * meta_table, T &ref) {
  auto data = static_cast<T **>(lua_newuserdata(lua, sizeof(T*)));
  *data = &ref;
  luaL_getmetatable(lua, meta_table);
  lua_setmetatable(lua, -2);
}

template <typename T>
inline int get_trivially_copyable_class_reference(lua_State *lua) {
  const auto table_name = lua_tostring(lua, lua_upvalueindex(1));
  auto c = static_cast<T **>(luaL_checkudata(lua, 1, table_name));
  push<T>(lua, **c);
  return 1;
}

template <typename T>
inline int set_trivially_copyable_class_reference(lua_State *lua) {
  const auto table_name = lua_tostring(lua, lua_upvalueindex(1));
  auto c = static_cast<T **>(luaL_checkudata(lua, 1, table_name));
  **c = arg_check<T>(lua, 2);
  return 0;
}

#if 0
template <typename T>
inline void initialize_trivially_copyable_class_reference(lua_State *lua, const char *table_name, int meta_meta_table) {
  luaL_newmetatable(lua, table_name);
  lua_pushstring(lua, table_name);
  lua_pushcclosure(lua, set_trivially_copyable_class_reference<T>, 1);
  lua_setfield(lua, -2, "set");
  lua_pushstring(lua, table_name);
  lua_pushcclosure(lua, get_trivially_copyable_class_reference<T>, 1);
  lua_setfield(lua, -2, "get");
  lua_pushvalue(lua, 1);
  //lua_pushvalue(lua, 1);
  lua_setfield(lua, -2, "__index");
  //lua_setfield(lua, -2, "__newindex");
  lua_rawgeti(lua, LUA_REGISTRYINDEX, meta_meta_table);
  lua_setmetatable(lua, -2);
  luaL_ref(lua, LUA_REGISTRYINDEX);
}

inline int make_meta_meta_table(lua_State *lua) {
  luaL_newmetatable(lua, "yutolua.ref.meta");
  lua_pushcfunction(lua, detail::reference_error);
  lua_setfield(lua, -2, "__index");
  lua_pushcfunction(lua, detail::reference_error);
  lua_setfield(lua, -2, "__newindex");
  return luaL_ref(lua, LUA_REGISTRYINDEX);
}

inline void reference_initialize(lua_State *lua) {
  const int meta_meta_table = make_meta_meta_table(lua);
  initialize_trivially_copyable_class_reference<bool>(lua, "yutolua.bool.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<char>(lua, "yutolua.char.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<signed char>(lua, "yutolua.schar.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<unsigned char>(lua, "yutolua.uchar.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<short>(lua, "yutolua.short.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<unsigned short>(lua, "yutolua.ushort.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<int>(lua, "yutolua.int.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<unsigned int>(lua, "yutolua.uint.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<long>(lua, "yutolua.long.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<unsigned long>(lua, "yutolua.ulong.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<float>(lua, "yutolua.float.ref", meta_meta_table);
  initialize_trivially_copyable_class_reference<double>(lua, "yutolua.double.ref", meta_meta_table);
  luaL_unref(lua, LUA_REGISTRYINDEX, meta_meta_table);
}
#endif
}}

#endif
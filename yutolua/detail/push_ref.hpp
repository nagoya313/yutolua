#ifndef YUTOLUA_DETAIL_PUSH_REF_HPP_
#define YUTOLUA_DETAIL_PUSH_REF_HPP_
#include "metatable.hpp"

namespace yutolua { namespace detail {
inline void push_ref(lua_State *lua, bool &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.bool.ref", value);
}

inline void push_ref(lua_State *lua, char &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.char.ref", value);
}

inline void push_ref(lua_State *lua, signed char &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.schar.ref", value);
}

inline void push_ref(lua_State *lua, unsigned char &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.uchar.ref", value);
}

inline void push_ref(lua_State *lua, short &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.short.ref", value);
}

inline void push_ref(lua_State *lua, unsigned short &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.ushort.ref", value);
}

inline void push_ref(lua_State *lua, int &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.int.ref", value);
}

inline void push_ref(lua_State *lua, unsigned int &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.uint.ref", value);
}

inline void push_ref(lua_State *lua, long &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.long.ref", value);
}

inline void push_ref(lua_State *lua, unsigned long &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.ulong.ref", value);
}

inline void push_ref(lua_State *lua, float &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.float.ref", value);
}

inline void push_ref(lua_State *lua, double &value) {
  new_trivially_copyable_class_reference(lua, "yutolua.double.ref", value);
}
}}

#endif
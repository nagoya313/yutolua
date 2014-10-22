#ifndef YUTOLUA_DETAIL_GLOVAL_REF_HPP_
#define YUTOLUA_DETAIL_GLOVAL_REF_HPP_
#include <memory>

namespace yutolua { namespace detail {
inline
std::shared_ptr<int> make_global_ref(lua_State *lua, const char *identify) {
  lua_getglobal(lua, identify);
  return std::shared_ptr<int>(new int{luaL_ref(lua, LUA_REGISTRYINDEX)},
                              [lua] (int *i) {
                                luaL_unref(lua, LUA_REGISTRYINDEX, *i);
                                delete i;
                              });
  }
}}

#endif
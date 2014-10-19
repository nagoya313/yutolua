#ifndef YUTOLUA_STATE_HPP_
#define YUTOLUA_STATE_HPP_
#include <memory>
//#include <boost/filesystem/path.hpp>
#include <boost/utility/string_ref.hpp>
#include "exception.hpp"
#include "detail/close.hpp"
#include "detail/complex.hpp"

namespace yutolua {
using unique_state = std::unique_ptr<lua_State, detail::close>;

inline unique_state make_state() {
  unique_state vm{luaL_newstate()};
  if (!vm) {
    throw bad_open{};
  }
  return vm;
}

inline void open_libs(const unique_state &lua) {
  luaL_openlibs(lua.get());
}


inline int error(lua_State *lua) {
  lua_pushstring(lua, "error");
  return lua_error(lua);
}
inline void initialize(const unique_state &lua) {
  detail::complex_initialize(lua.get());
  /*lua_getglobal(lua.get(), "_G");
  lua_getmetatable(lua.get(), -1);
  luaL_newmetatable(lua.get(), "yutolua.ref");
  lua_pushcfunction(lua.get(), error);
  luaL_newmetatable(lua.get(), "yutolua.ref");
  lua_setfield(lua.get(), -2, "__index");
  lua_setmetatable(lua.get(), -2);
  lua_setglobal(lua.get(), "_G");*/
  /*luaL_newmetatable(lua.get(), "yutolua.bool.ref");
  lua_pushvalue(lua.get(), 1);
  lua_setfield(lua.get(), -2, "__index");*/
}

inline void do_file(const unique_state &lua, const boost::string_ref &path) {
  if (luaL_dofile(lua.get(), path.data())) {
    throw bad_load{} << panic_info{lua_tostring(lua.get(), -1)};// << file_name_info{path};
  }
}

inline
void do_string(const unique_state &lua, boost::string_ref code) {
  if (luaL_dostring(lua.get(), code.data())) {
    throw bad_load{} << panic_info{lua_tostring(lua.get(), -1)};
  }
}
}

#endif
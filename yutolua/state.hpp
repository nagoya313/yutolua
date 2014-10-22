#ifndef YUTOLUA_STATE_HPP_
#define YUTOLUA_STATE_HPP_
#include <memory>
#include <boost/filesystem/path.hpp>
#include <boost/utility/string_ref.hpp>
#include "exception.hpp"
#include "detail/state.hpp"

namespace yutolua {
using unique_state = std::unique_ptr<lua_State, detail::close>;
using shared_state = std::shared_ptr<lua_State>;

inline unique_state make_unique_state() {
  unique_state vm{luaL_newstate()};
  if (!vm) {
    throw panic_error{};
  }
  return vm;
}

inline shared_state make_shared_state() {
  shared_state vm{luaL_newstate(), detail::close{}};
  if (!vm) {
    throw panic_error{};
  }
  return vm;
}

inline void use_panic_exception(lua_State *lua) {
  lua_atpanic(lua, [](lua_State *lua) -> int {
    throw panic_error{} << panic_info{lua_tostring(lua, -1)};
  });
}

inline void use_panic_exception(const unique_state &lua) {
  use_panic_exception(lua.get());
}

inline void use_panic_exception(const shared_state &lua) {
  use_panic_exception(lua.get());
}

inline void open_libs(lua_State *lua) {
  luaL_openlibs(lua);
}

inline void open_libs(const unique_state &lua) {
  open_libs(lua.get());
}

inline void open_libs(const shared_state &lua) {
  open_libs(lua.get());
}

inline void do_file(lua_State *lua, const boost::filesystem::path &path) {
  if (luaL_dofile(lua, path.string().c_str())) {
    throw panic_error{} << panic_info{lua_tostring(lua, -1)} << file_name_info{path};
  }
}

inline void do_file(const unique_state &lua, const boost::filesystem::path &path) {
  do_file(lua.get(), path);
}

inline void do_file(const shared_state &lua, const boost::filesystem::path &path) {
  do_file(lua.get(), path);
}

inline void do_string(lua_State *lua, boost::string_ref code) {
  if (luaL_dostring(lua, code.data())) {
    throw panic_error{} << panic_info{lua_tostring(lua, -1)};
  }
}

inline void do_string(const unique_state &lua, boost::string_ref code) {
  do_string(lua.get(), code);
}

inline void do_string(const shared_state &lua, boost::string_ref code) {
  do_string(lua.get(), code);
}
}

#endif
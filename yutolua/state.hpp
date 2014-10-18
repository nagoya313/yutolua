#ifndef YUTOLUA_STATE_HPP_
#define YUTOLUA_STATE_HPP_
#include <memory>
#include <boost/filesystem/path.hpp>
#include <boost/utility/string_ref.hpp>
#include "exception.hpp"
#include "detail/close.hpp"

namespace yutolua {
using unique_state = std::unique_ptr<lua_State, detail::close>;

inline
unique_state make_state() {
  unique_state vm{luaL_newstate()};
  if (!vm) {
    throw bad_open{};
  }
  return vm;
}

inline
void open_libs(const unique_state &lua) {
  luaL_openlibs(lua.get());
}

inline
void do_file(const unique_state &lua, const boost::filesystem::path &path) {
  if (luaL_dofile(lua.get(), path.string().c_str())) {
    throw bad_load{} << panic_info{lua_tostring(lua.get(), -1)} << file_name_info{path};
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
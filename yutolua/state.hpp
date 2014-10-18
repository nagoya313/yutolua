#ifndef YUTOLUA_HPP_
#define YUTOLUA_HPP_
#include <memory>
#include <boost/filesystem/path.hpp>
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
void do_file(const unique_state &vm, const boost::filesystem::path &path) {
  if (luaL_dofile(vm.get(), path.string().c_str())) {
    throw bad_load{} << panic_info{lua_tostring(vm.get(), -1)} << file_name_info{path};
  }
}
}

#endif
#include <iostream>
#include <lua.hpp>
#include <yutolua/state.hpp>
#include <yutolua/c_function.hpp>

void cpp_function(const std::string &str) {
  std::cout << str << std::endl;
}

int main() {
  try {
    yutolua::unique_state lua{yutolua::make_state()};
    yutolua::open_libs(lua);
    yutolua::define(lua, "cpp_function", cpp_function);
    yutolua::do_string(lua, "cpp_function('Hello Lua!');");
  } catch (const yutolua::exception &err) {
    std::cerr << diagnostic_information(err) << std::endl;
  }
}
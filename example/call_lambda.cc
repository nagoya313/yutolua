#include <iostream>
#include <lua.hpp>
#include <yutolua/state.hpp>
#include <yutolua/c_function.hpp>

int main() {
  try {
    yutolua::unique_state lua{yutolua::make_state()};
    yutolua::open_libs(lua);
    yutolua::define(lua, "cpp_lambda", [](const std::string &str) {
      std::cout << str << std::endl;
    });
    yutolua::do_string(lua, "cpp_lambda('Hello Lua!');");
  } catch (const yutolua::exception &err) {
    std::cerr << diagnostic_information(err) << std::endl;
  }
}
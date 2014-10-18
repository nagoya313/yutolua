#include <iostream>
#include <lua.hpp>
#include <yutolua/state.hpp>

int main() {
  try {
    yutolua::unique_state lua{yutolua::make_state()};
    yutolua::open_libs(lua);
    yutolua::do_string(lua, "print('Hello Lua!');");
  } catch (const yutolua::exception &err) {
    std::cerr << diagnostic_information(err) << std::endl;
  }
}

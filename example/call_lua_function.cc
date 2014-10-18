#include <iostream>
#include <lua.hpp>
#include <yutolua/state.hpp>
#include <yutolua/function.hpp>

int main() {
  try {
    yutolua::unique_state lua{yutolua::make_state()};
    yutolua::open_libs(lua);
    yutolua::do_string(lua, "function add(x, y) return x + y; end");
    yutolua::function<int (int, int)> lua_func{lua, "add"};
    std::cout << lua_func(1, 2) << std::endl;
  } catch (const yutolua::exception &err) {
    std::cerr << diagnostic_information(err) << std::endl;
  }
}
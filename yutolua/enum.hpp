#ifndef YUTOLUA_ENUM_HPP_
#define YUTOLUA_ENUM_HPP_
#include <initializer_list>
#include <string>
#include <boost/utility/string_ref.hpp>
#include "state.hpp"
#include "detail/enum_meta.hpp"

namespace yutolua {
template <typename Enum>
struct enum_value {
  std::string key;
  Enum value;
};

template <typename Enum>
enum_value<Enum> make_enum(boost::string_ref key, Enum value) {
  return {key, value};
}

template <typename Enum>
void enum_define(const unique_state &lua, boost::string_ref identify, std::initializer_list<Enum> list) {
  lua_newtable(lua.get());
  luaL_newmetatable(lua.get(), identify.data());
  for (const auto &e: list) {
    lua_pushinteger(lua.get(), static_cast<int>(e.value));
    lua_setfield(lua.get(), -2, e.key.c_str());
  }
  luaL_newmetatable(lua.get(), (std::string("meta") + std::string(identify)).c_str());
  lua_pushcfunction(lua.get(), detail::enum_not_find_error);
  lua_setfield(lua.get(), -2, "__index");
  lua_setmetatable(lua.get(), -2);
  lua_setfield(lua.get(), -2, "__index");
  lua_pushcfunction(lua.get(), detail::enum_assign_error);
  lua_setfield(lua.get(), -2, "__newindex");
  lua_setmetatable(lua.get(), -2);
  lua_setglobal(lua.get(), identify.data());
}
}

#endif
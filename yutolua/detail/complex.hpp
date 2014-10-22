#ifndef YUTOLUA_DETAIL_COMPLEX_HPP_
#define YUTOLUA_DETAIL_COMPLEX_HPP_
#include <complex>
#include <string>

namespace yutolua { namespace detail {
inline int undefined_complex_member(lua_State *lua) {
  const std::string member = lua_tostring(lua, 2);
  lua_pushstring(lua, ("'struct complex' has no member named '" + member + "'").c_str());
  return lua_error(lua);
}

template <typename T>
inline int new_complex(lua_State *lua) {
  auto complex = static_cast<std::complex<T> **>(lua_newuserdata(lua, sizeof(std::complex<T> *)));
  const auto real = luaL_checknumber(lua, 1);
  const auto imag = luaL_checknumber(lua, 2);
  try {
    *complex = new std::complex<T>{real, imag};
  } catch (const std::bad_alloc &err) {
    lua_pushstring(lua, err.what());
    return lua_error(lua);
  }
  luaL_getmetatable(lua, "yutolua.complex");
  lua_setmetatable(lua, -2);
  return 1;
}

template <typename T>
inline int real_complex(lua_State *lua) {
  auto c = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  lua_pushnumber(lua, (*c)->real());
  return 1;
}

template <typename T>
inline int imag_complex(lua_State *lua) {
  auto c = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  lua_pushnumber(lua, (*c)->imag());
  return 1;
}

template <typename T>
inline int add_complex(lua_State *lua) {
  auto l = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  auto r = static_cast<std::complex<T> **>(luaL_checkudata(lua, 2, "yutolua.complex"));
  auto complex = static_cast<std::complex<T> **>(lua_newuserdata(lua, sizeof(std::complex<T> *)));
  try {
    *complex = new std::complex<T>(**l + **r);
  } catch (const std::bad_alloc &err) {
    lua_pushstring(lua, err.what());
    return lua_error(lua);
  }
  luaL_getmetatable(lua, "yutolua.complex");
  lua_setmetatable(lua, -2);
  return 1;
}

template <typename T>
inline int sub_complex(lua_State *lua) {
  auto l = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  auto r = static_cast<std::complex<T> **>(luaL_checkudata(lua, 2, "yutolua.complex"));
  auto complex = static_cast<std::complex<T> **>(lua_newuserdata(lua, sizeof(std::complex<T> *)));
  try {
    *complex = new std::complex<T>(**l - **r);
  } catch (const std::bad_alloc &err) {
    lua_pushstring(lua, err.what());
    return lua_error(lua);
  }
  luaL_getmetatable(lua, "yutolua.complex");
  lua_setmetatable(lua, -2);
  return 1;
}

template <typename T>
inline int mul_complex(lua_State *lua) {
  auto l = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  auto r = static_cast<std::complex<T> **>(luaL_checkudata(lua, 2, "yutolua.complex"));
  auto complex = static_cast<std::complex<T> **>(lua_newuserdata(lua, sizeof(std::complex<T> *)));
  try {
    *complex = new std::complex<T>(**l * **r);
  } catch (const std::bad_alloc &err) {
    lua_pushstring(lua, err.what());
    return lua_error(lua);
  }
  luaL_getmetatable(lua, "yutolua.complex");
  lua_setmetatable(lua, -2);
  return 1;
}

template <typename T>
inline int div_complex(lua_State *lua) {
  auto l = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  auto r = static_cast<std::complex<T> **>(luaL_checkudata(lua, 2, "yutolua.complex"));
  auto complex = static_cast<std::complex<T> **>(lua_newuserdata(lua, sizeof(std::complex<T> *)));
  try {
    *complex = new std::complex<T>(**l / **r);
  } catch (const std::bad_alloc &err) {
    lua_pushstring(lua, err.what());
    return lua_error(lua);
  }
  luaL_getmetatable(lua, "yutolua.complex");
  lua_setmetatable(lua, -2);
  return 1;
}

template <typename T>
inline int delete_complex(lua_State *lua) {
  auto c = static_cast<std::complex<T> **>(luaL_checkudata(lua, 1, "yutolua.complex"));
  delete *c;
  return 0;
}

inline void complex_initialize(lua_State *lua) {
  luaL_newmetatable(lua, "yutolua.complex");
  lua_pushvalue(lua, 1);
  lua_setfield(lua, -2, "__index");
  const luaL_Reg complex_lib_meta[] = {
    {"real", real_complex<double>},
    {"imag", imag_complex<double>},
    {"__add", add_complex<double>},
    {"__sub", sub_complex<double>},
    {"__mul", mul_complex<double>},
    {"__div", div_complex<double>},
    {"__gc", delete_complex<double>},
    {nullptr, nullptr}
  };
  luaL_setfuncs(lua, complex_lib_meta, 0);
  luaL_newmetatable(lua, "yutolua.complex.nomember");
  lua_pushcfunction(lua, undefined_complex_member);
  lua_setfield(lua, -2, "__index");
  lua_setmetatable(lua, -2);
  luaL_ref(lua, LUA_REGISTRYINDEX);
  const luaL_Reg complex_lib[] = {
    {"new", new_complex<double>},
    {nullptr, nullptr}
  };
  luaL_newlibtable(lua, complex_lib);
  luaL_setfuncs(lua, complex_lib, 0);
  lua_setglobal(lua, "complex");
}
}}

#endif
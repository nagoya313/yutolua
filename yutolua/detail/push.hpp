#ifndef YUTOLUA_DETAIL_PUSH_HPP_
#define YUTOLUA_DETAIL_PUSH_HPP_
#include <array>
#include <complex>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <boost/optional.hpp>

namespace yutolua { namespace detail {
inline void push(lua_State *lua, std::nullptr_t) {
  lua_pushnil(lua);
}

inline void push(lua_State *lua, bool value) {
  lua_pushboolean(lua, value);
}

template <typename T>
inline void new_trivially_copyable_class(lua_State *lua, const char * meta_table, T &ref) {
  auto data = static_cast<T **>(lua_newuserdata(lua, sizeof(T*)));
  *data = &ref;
  luaL_getmetatable(lua, meta_table);
  lua_setmetatable(lua, -2);
}

inline void push_ref(lua_State *lua, bool &value) {
  new_trivially_copyable_class(lua, "yutolua.bool.ref", value);
}

inline void push_cref(lua_State *lua, const bool &value) {
  push(lua, value);
}

inline void push(lua_State *lua, int value) {
  lua_pushinteger(lua, value);
}
inline void push_cref(lua_State *lua, const int &value) {
  push(lua, value);
}

inline void push(lua_State *lua, unsigned value) {
  lua_pushunsigned(lua, value);
}

inline void push_cref(lua_State *lua, unsigned value) {
  push(lua, value);
}

inline void push(lua_State *lua, double value) {
  lua_pushnumber(lua, value);
}

inline void push_cref(lua_State *lua, const double &value) {
  push(lua, value);
}

inline void push(lua_State *lua, void *value) {
  lua_pushlightuserdata(lua, value);
}

inline void push(lua_State *lua, const char *value) {
  lua_pushstring(lua, value);
}

inline void push(lua_State *lua, const std::string &value) {
  lua_pushlstring(lua, value.data(), value.size());
}

inline void push_cref(lua_State *lua, const std::string &value) {
  push(lua, value);
}

template <typename T>
inline void push(lua_State *lua, const boost::optional<T> &value) {
  if (value) {
    push(lua, *value);
  } else {
    push(lua, nullptr);
  }
}

template <typename Range>
inline void push_array(lua_State *lua, const Range &range) {
  lua_newtable(lua);
  int i = 1;
  for (const auto &v: range) {
    push(lua, v);
    lua_rawseti(lua, lua_gettop(lua) - 1, i++);
  }
}

template <typename T, std::size_t Size>
inline void push(lua_State *lua, T (&value)[Size]) {
  push_array(lua, value);
}

template <typename T, std::size_t Size>
inline void push(lua_State *lua, std::array<T, Size> &value) {
  push_array(lua, value);
}

template <typename T>
inline void push(lua_State *lua, std::vector<T> &value) {
  push_array(lua, value);
}

template <typename First, typename Second>
inline void push(lua_State *lua, const std::pair<First, Second> &value) {
  lua_newtable(lua);
  push(lua, value.first);
  lua_setfield(lua, -2, "first");
  push(lua, value.second);
  lua_setfield(lua, -2, "second");
}

template <int Index, typename... Values>
inline void push_tuple(lua_State *lua, const std::tuple<Values...> &value) {
  if (Index < std::tuple_size<std::tuple<Values...>>::value) {
    push(lua, std::get<Index>(value));
    lua_rawseti(lua, lua_gettop(lua) - 1, Index + 1);
    push_tuple<Index + 1>(lua, value);
  }
}

template <typename... Values>
inline void push(lua_State *lua, const std::tuple<Values...> &value) {
  lua_newtable(lua);
  push_tuple<0>(lua, value)
}

template <typename T>
inline void push(lua_State *lua, const std::complex<T> &value) {
  lua_newtable(lua);
  push(lua, value.real());
  lua_setfield(lua, -2, "real");
  push(lua, value.imag());
  lua_setfield(lua, -2, "imag");
  luaL_getmetatable(lua, "complex");
  lua_setmetatable(lua, -2);
}
}}

#endif
#ifndef YUTOLUA_DETAIL_GET_HPP_
#define YUTOLUA_DETAIL_GET_HPP_
#include <array>
#include <string>
#include <type_traits>
#include <vector>
#include <boost/optional.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/range/irange.hpp>
#include "auto_pop.hpp"
#include "type_check.hpp"

namespace yutolua { namespace detail {
extern void *enabler;

template <typename T, typename std::enable_if<std::is_same<T, bool>::value>::type *& = enabler>
bool get(lua_State *lua, int index) {
  return lua_toboolean(lua, index) != 0;
}

template <typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value>::type *& = enabler>
lua_Integer get(lua_State *lua, int index) {
  return lua_tointeger(lua, index);
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value && !boost::is_same<T, bool>::value>::type *& = enabler>
lua_Unsigned get(lua_State *lua, int index) {
  return lua_tounsigned(lua, index);
}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *& = enabler>
lua_Number get(lua_State *lua, int index) {
  return lua_tonumber(lua, index);
}

template <typename T, typename std::enable_if<std::is_same<T, std::string>::value>::type *& = enabler>
const char *get(lua_State *lua, int index) {
  return lua_tostring(lua, index);
}

template <typename T, typename std::enable_if<is_optional<T>::value>::type *& = enabler>
T get(lua_State *lua, int index) {
  return lua_type(lua, index) == LUA_TNIL ? boost::none : boost::make_optional(convert<T::value_type>(lua, index));
}

template <typename T, typename std::enable_if<is_std_array<T>::value>::type *& = enabler>
T get(lua_State *lua, int index) {
  type_check<LUA_TTABLE>(lua_type(lua, index));
  T array;
  boost::transform(boost::irange<int>(1, std::tuple_size<T>::value + 1), array.begin(), [lua, index](int i) {
    lua_rawgeti(lua, index, i);
    auto_pop<1> pop{lua};
    return convert<typename T::value_type>(lua, -1);
  });
  return array;
}

template <typename T, typename std::enable_if<is_std_vector<T>::value>::type *& = enabler>
T get(lua_State *lua, int index) {
  type_check<LUA_TTABLE>(lua_type(lua, index));
  T vector;
  for (int i = 1;; ++i) {
    lua_rawgeti(lua, index, i);
    auto_pop<1> pop{lua};
    if (lua_type(lua, -1) == LUA_TNIL) {
      break;
    }
    vector.emplace_back(convert<typename T::value_type>(lua, -1));
  }
  return vector;
}
}}

#endif
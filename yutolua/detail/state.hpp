#ifndef YUTOLUA_DETAIL_STATE_HPP_
#define YUTOLUA_DETAIL_STATE_HPP_

namespace yutolua { namespace detail {
struct close {
  void operator ()(lua_State *lua) const {
    lua_close(lua);
  }
};
}}

#endif
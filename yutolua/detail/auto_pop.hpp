#ifndef YUTOLUA_DETAIL_AUTO_POP_HPP_
#define YUTOLUA_DETAIL_AUTO_POP_HPP_
#include <boost/noncopyable.hpp>

namespace yutolua { namespace detail {
template <int N>
struct auto_pop : boost::noncopyable {
  explicit auto_pop(lua_State *lua) : lua_{lua} {}

  ~auto_pop() {
    lua_pop(lua_, N);
  }

 private:
  lua_State *lua_;
};

struct auto_top : boost::noncopyable {
  explicit auto_top(lua_State *lua) : lua_{lua}, top_{lua_gettop(lua_)} {}

  ~auto_top() {
    lua_settop(lua_, top_);
  }

 private:
  lua_State *lua_;
  int top_;
};
}}

#endif
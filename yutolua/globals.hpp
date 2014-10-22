#ifndef YUTOLUA_GLOBALS_HPP_
#define YUTOLUA_GLOBALS_HPP_
#include <functional>
#include <boost/utility/string_ref.hpp>
#include "object.hpp"
#include "state.hpp"
#include "detail/c_function.hpp"
#include "detail/type_check.hpp"

namespace yutolua {
struct globals {
  explicit globals(lua_State *lua) : lua_{lua} {}
  explicit globals(const unique_state &lua) : lua_{lua.get()} {}
  explicit globals(const shared_state &lua) : lua_{lua.get()} {}

  object operator [](boost::string_ref identify) const {
    return {lua_, identify};
  }

  template <typename Result, typename... Args>
  void def(boost::string_ref identify, Result (*func)(Args...)) {
    lua_pushcfunction(lua_, reinterpret_cast<lua_CFunction>(func));
    lua_pushcclosure(lua_, detail::c_function<Result (Args...)>::call, 1);
    lua_setglobal(lua_, identify.data());
  }

  template <typename Lambda, detail::match_comvertible_function_ptr<Lambda> *& = detail::enabler>
  void def(boost::string_ref identify, Lambda lambda) {
    def(identify, detail::lamba_to_function_ptr(lambda));
  }

  template <typename Result, typename... Args>
  void def(boost::string_ref identify, std::function<Result (Args...)> func) {
    detail::new_function(lua_, identify, func);
    lua_setglobal(lua_, identify.data());
  }

 private:
  lua_State *lua_;
};
}

#endif
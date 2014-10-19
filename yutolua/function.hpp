#ifndef YUTOLUA_FUNCTION_HPP_
#define YUTOLUA_FUNCTION_HPP_
#include <memory>
#include <string>
#include <boost/utility/string_ref.hpp>
#include "exception.hpp"
#include "state.hpp"
#include "detail/args_push.hpp"
#include "detail/result_size.hpp"
#include "detail/result_values.hpp"

namespace yutolua {
template <typename>
class function;

template <typename Result, typename... Args>
class function<Result (Args...)> {
 public:
  function(const unique_state &lua, boost::string_ref identify) : lua_{lua.get()} {
    initialize(identify);
  }

  function(lua_State *lua, boost::string_ref identify) : lua_{lua} {
    initialize(identify);
  }

  Result operator ()(Args... args) const {
    lua_rawgeti(lua_, LUA_REGISTRYINDEX, *ref_);
    detail::args_push(lua_, args...);
    if (lua_pcall(lua_, sizeof...(Args), detail::result_size<Result>::value, 0)) {
      throw bad_function_call{} << panic_info{lua_tostring(lua_, -1)};
    }
    return detail::result_values<Result>{}(lua_);
  }

 private:
  void initialize(boost::string_ref identify) {
    lua_getglobal(lua_, identify.data());
    ref_ = std::shared_ptr<int>(new int{luaL_ref(lua_, LUA_REGISTRYINDEX)},
                                [this] (int *i) {
                                  luaL_unref(lua_, LUA_REGISTRYINDEX, *i);
                                  delete i;
                                });
  }

  lua_State *lua_;
  std::shared_ptr<int> ref_;
};
}

#endif
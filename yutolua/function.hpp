#ifndef YUTOLUA_FUNCTION_HPP_
#define YUTOLUA_FUNCTION_HPP_
#include <memory>
#include <string>
#include "exception.hpp"
#include "state.hpp"
#include "detail/args_push.hpp"
#include "detail/global_ref.hpp"
#include "detail/result_size.hpp"
#include "detail/result_values.hpp"

namespace yutolua {
template <typename>
class function;

template <typename Result, typename... Args>
class function<Result (Args...)> {
 public:
  function(lua_State *lua, const char *identify) : lua_{lua}, ref_{detail::make_global_ref(lua_, identify)} {}
  function(lua_State *lua, const std::string &identify) : function{lua, identify.c_str()} {}
  function(const unique_state &lua, const char *identify) : function{lua.get(), identify} {}
  function(const unique_state &lua, const std::string &identify) : function{lua.get(), identify.c_str()} {}
  function(const shared_state &lua, const char *identify) : function{lua.get(), identify} {}
  function(const shared_state &lua, const std::string &identify) : function{lua.get(), identify.c_str()} {}

  Result operator ()(Args... args) const {
    lua_rawgeti(lua_, LUA_REGISTRYINDEX, *ref_);
    detail::args_push<Args...>(lua_, std::forward<Args>(args)...);
    if (lua_pcall(lua_, sizeof...(Args), detail::result_size<Result>::value, 0)) {
      throw bad_function_call{} << panic_info{lua_tostring(lua_, -1)};
    }
    return detail::result_values<Result>{}(lua_);
  }

 private:
  lua_State *lua_;
  std::shared_ptr<int> ref_;
};
}

#endif
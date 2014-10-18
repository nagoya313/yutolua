#ifndef YUTOLUA_FUNCTION_HPP_
#define YUTOLUA_FUNCTION_HPP_
#include <string>
#include <boost/noncopyable.hpp>
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
class function<Result (Args...)> : boost::noncopyable {
 public:
  function(const unique_state &lua, boost::string_ref identify) : lua_{lua.get()}, identify_(identify) {}

  Result operator ()(const Args &... args) const {
    lua_getglobal(lua_, identify_.c_str());
    detail::args_push(lua_, args...);
    if (lua_pcall(lua_, sizeof...(Args), detail::result_size<Result>::value, 0)) {
      throw bad_function_call{} << panic_info{lua_tostring(lua_, -1)};
    }
    return detail::result_values<Result>{}(lua_);
  }

 private:
  lua_State *lua_;
  std::string identify_;
};
}

#endif
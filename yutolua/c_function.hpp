#ifndef YUTOLUA_C_FUNCTION_HPP_
#define YUTOLUA_C_FUNCTION_HPP_
#include <boost/utility/string_ref.hpp>
#include "state.hpp"
#include "detail/c_function.hpp"
#include "detail/type_check.hpp"

namespace yutolua {
template <typename Result, typename... Args>
void define(const unique_state &lua, boost::string_ref identify, Result (*func)(Args...)) {
  lua_pushcfunction(lua.get(), reinterpret_cast<lua_CFunction
  >(func));
  lua_pushcclosure(lua.get(), detail::c_function<Result (Args...)>::call, 1);
  lua_setglobal(lua.get(), identify.data());
}

template <typename Lambda>
void define(const unique_state &lua, boost::string_ref identify, Lambda lambda) {
  define(lua, identify, detail::lamba_to_function_ptr(&Lambda::operator (), lambda));
}
}

#endif
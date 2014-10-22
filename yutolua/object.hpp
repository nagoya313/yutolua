#ifndef YUTOLUA_OBJECT_HPP_
#define YUTOLUA_OBJECT_HPP_
#include <string>
#include <utility>
#include <boost/utility/string_ref.hpp>
#include "detail/auto_pop.hpp"
#include "detail/get.hpp"
#include "detail/push.hpp"

namespace yutolua {
struct object {
  object(lua_State *lua, boost::string_ref identify) : lua_{lua}, identify_(identify) {}

  template <typename T>
  object &operator =(T value) {
    detail::push<T>(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

  template <typename T>
  operator T() const {
    lua_getglobal(lua_, identify_.c_str());
    detail::auto_pop<1> pop{lua_};
    return detail::get<T>(lua_, -1);
  }

 private:
  lua_State *lua_;
  std::string identify_;
};
}

#endif
#ifndef YUTOLUA_OBJECT_HPP_
#define YUTOLUA_OBJECT_HPP_
#include <string>
#include <utility>
#include <boost/utility/string_ref.hpp>
#include "detail/push.hpp"

namespace yutolua {
struct object {
  object(lua_State *lua, boost::string_ref identify) : lua_{lua}, identify_(identify) {}

  object(const object &rhs) = default;
  object &operator =(const object &rhs) = default;
  object(object &&rhs) : lua_{std::move(rhs.lua_)}, identify_(std::move(rhs.identify_)) {}

  object &operator =(object &&rhs) {
    lua_ = std::move(rhs.lua_);
    identify_ = std::move(rhs.identify_);
    return *this;
  }

  template <typename T>
  object &operator =(T value) {
    detail::push(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

  template <typename T>
  object &operator =(std::reference_wrapper<T> value) {
    detail::push_ref(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

  template <typename T>
  object &operator =(std::reference_wrapper<const T> value) {
    detail::push_cref(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

 private:
  lua_State *lua_;
  std::string identify_;
};
}

#endif
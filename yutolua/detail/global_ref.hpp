#ifndef YUTOLUA_DETAIL_GLOVAL_REF_HPP_
#define YUTOLUA_DETAIL_GLOVAL_REF_HPP_
#include <string>
#include <boost/utility/string_ref.hpp>
#include "auto_pop.hpp"
#include "convert.hpp"
#include "get.hpp"
#include "push.hpp"

namespace yutolua { namespace detail {
struct global_ref {
  global_ref(lua_State *lua, boost::string_ref identify) : lua_{lua}, identify_(identify) {}

  global_ref(const global_ref &rhs) = default;
  global_ref &operator =(const global_ref &rhs) = default;
  global_ref(global_ref &&rhs) : lua_{std::move(rhs.lua_)}, identify_(std::move(rhs.identify_)) {}
  global_ref &operator =(global_ref &&rhs) {
    lua_ = std::move(rhs.lua_);
    identify_ = std::move(rhs.identify_);
    return *this;
  }

  template <typename T>
  global_ref &operator =(T value) {
    push(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

  template <typename T>
  global_ref &operator =(std::reference_wrapper<T> value) {
    return *this;
  }

  template <typename T>
  global_ref &operator =(std::reference_wrapper<const T> value) {
    push_cref(lua_, value);
    lua_setglobal(lua_, identify_.c_str());
    return *this;
  }

  template <typename T>
  operator T() const {
    lua_getglobal(lua_, identify_.c_str());
    auto_pop<1> pop{lua_};
    return convert<T>(lua_, lua_gettop(lua_));
  }

 private:
  lua_State *lua_;
  std::string identify_;
};
}}

#endif
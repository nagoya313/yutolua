#ifndef YUTOLUA_GLOBALS_HPP_
#define YUTOLUA_GLOBALS_HPP_
#include <boost/utility/string_ref.hpp>
#include "state.hpp"
#include "detail/convert.hpp"
#include "detail/global_ref.hpp"
#include "detail/push.hpp"

namespace yutolua {
struct globals {
  explicit globals(const unique_state &lua) : lua_{lua.get()} {}

  detail::global_ref operator [](boost::string_ref identify) const {
    return {lua_, identify};
  }

 private:
  lua_State *lua_;
};
}

#endif
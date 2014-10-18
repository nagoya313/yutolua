#ifndef YUTOLUA_OBJECT_CAST_HPP_
#define YUTOLUA_OBJECT_CAST_HPP_
#include "detail/global_ref.hpp"

namespace yutolua {
template <typename Target>
Target object_cast(const detail::global_ref &ref) {
  return static_cast<Target>(ref);
}
}

#endif
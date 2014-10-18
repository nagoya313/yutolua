#ifndef YUTOLUA_DETAIL_TYPE_CHECK_HPP_
#define YUTOLUA_DETAIL_TYPE_CHECK_HPP_
#include <array>
#include <type_traits>
#include <vector>
#include <boost/optional.hpp>
#include "../exception.hpp"

namespace yutolua { namespace detail {
template <int Type>
void type_check(int type) {
  if (type != Type) {
    throw bad_cast{};
  }
}

template <typename Result, typename Lambda, typename... Args>
auto lamba_to_function_ptr(Result (Lambda:: *)(Args...) const, Lambda lambda) -> Result (*)(Args...) {
  return lambda;
}

template <typename T>
struct is_std_array : std::false_type {};

template <typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : std::true_type {};

template <typename T>
struct is_std_vector : std::false_type {};

template <typename T>
struct is_std_vector<std::vector<T>> : std::true_type {};

template <typename T>
struct is_optional : std::false_type {};

template <typename T>
struct is_optional<boost::optional<T>> : std::true_type {};
}}

#endif

#ifndef YUTOLUA_DETAIL_TYPE_CHECK_HPP_
#define YUTOLUA_DETAIL_TYPE_CHECK_HPP_
#include <cstddef>
#include <string>
#include <type_traits>

namespace yutolua { namespace detail {
extern void *enabler;

template <typename T>
using match_nil = std::enable_if_t<std::is_same<T, std::nullptr_t>::value>;
template <typename T>
using match_bool = std::enable_if_t<std::is_same<T, bool>::value>;
template <typename T>
using match_signed_integral = std::enable_if_t<std::is_signed<T>::value && std::is_integral<T>::value>;
template <typename T>
using match_unsigned_integral = std::enable_if_t<std::is_unsigned<T>::value && std::is_integral<T>::value && !std::is_same<T, bool>::value>;
template <typename T>
using match_floating_point = std::enable_if_t<std::is_floating_point<T>::value>;
template <typename T>
using match_c_string = std::enable_if_t<std::is_same<T, const char *>::value>;
template <typename T>
using match_string = std::enable_if_t<std::is_same<T, std::string>::value>;
template <typename T>
using match_arg_string = std::enable_if_t<std::is_same<T, std::string>::value || std::is_same<T, const std::string &>::value>;

template <typename T>
struct convert_function_ptr;

template <typename Lambda, typename Result, typename... Args>
struct convert_function_ptr<Result (Lambda:: *)(Args...) const> {
  using type = Result (*)(Args...);
};

template <typename T>
using convert_function_ptr_t = typename convert_function_ptr<T>::type;

template <typename Lambda>
inline convert_function_ptr_t<decltype(&Lambda::operator ())> lamba_to_function_ptr(Lambda lambda) {
  return lambda;
}

template <bool IsClass, typename T>
struct convert_function_ptr_switch {
  using type = convert_function_ptr_t<decltype(&T::operator ())>;
};

template <typename T>
struct convert_function_ptr_switch<false, T> {
  using type = void;
};

template <typename T>
struct is_function_pointer : std::integral_constant<bool, std::is_pointer<T>::value && std::is_function<std::remove_pointer_t<T>>::value> {};

template <typename T>
struct is_comvertible_function_ptr : std::is_convertible<T, typename convert_function_ptr_switch<std::is_class<T>::value, T>::type> {};

template <typename T>
using match_comvertible_function_ptr = std::enable_if_t<is_comvertible_function_ptr<T>::value>;
}}

#endif

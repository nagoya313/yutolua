#ifndef YUTOLUA_EXCEPTION_HPP_
#define YUTOLUA_EXCEPTION_HPP_
#include <exception>
#include <string>
#include <boost/config.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem/path.hpp>

namespace yutolua {
using panic_info = boost::error_info<struct panic, std::string>;
using file_name_info = boost::error_info<struct file_name, boost::filesystem::path>;
using type_info = boost::error_info<struct bad_cast_type, std::string>;

struct exception : virtual boost::exception, virtual std::exception {};

struct panic_error : virtual exception {
  const char *what() const BOOST_NOEXCEPT override {
    return "lua panic error.";
  }
};

struct bad_cast : virtual exception {
  const char *what() const BOOST_NOEXCEPT override {
    return "lua bad cast.";
  }
};

struct bad_function_call : virtual exception {
  const char *what() const BOOST_NOEXCEPT override {
    return "lua bad function call.";
  }
};
}

#endif
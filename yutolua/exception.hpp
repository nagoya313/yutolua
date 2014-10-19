#ifndef YUTOLUA_EXCEPTION_HPP_
#define YUTOLUA_EXCEPTION_HPP_
#include <exception>
#include <string>
#include <boost/exception/all.hpp>
//#include <boost/filesystem/path.hpp>

namespace yutolua {
using panic_info = boost::error_info<struct panic, std::string>;
//using file_name_info = boost::error_info<struct file_name, boost::filesystem::path>;

struct exception : virtual boost::exception, virtual std::exception {};
struct bad_open : virtual exception {};
struct bad_cast : virtual exception {};
struct bad_function_call : virtual exception {};
struct bad_load : virtual exception {};
}

#endif
#ifndef MPA_MPERROR_INCLUDE_MPAEXCEPT_H_
#define MPA_MPERROR_INCLUDE_MPAEXCEPT_H_

#include <stdexcept>
#include <string>

#ifdef _WIN32

// TODO: FIX
// non - DLL-interface class 'class_1'
// used as base for DLL-interface class 'class_2'
#pragma warning(disable : 4275)

#ifdef MPA_BUILD_ERROR_LIB
#define MPA_ERROR_EXPORT __declspec(dllexport)
#else
#define MPA_ERROR_EXPORT __declspec(dllimport)
#endif
#else
#define MPA_ERROR_EXPORT
#endif

namespace mpa {
namespace error {

class MPA_ERROR_EXPORT InvalidArgument : public std::invalid_argument {
 public:
  explicit InvalidArgument(const std::string& msg);
  explicit InvalidArgument(std::string&& msg);
  explicit InvalidArgument(const char* msg);
};

class MPA_ERROR_EXPORT InvalidNumber : public std::logic_error {
 public:
  explicit InvalidNumber(const std::string& msg);
  explicit InvalidNumber(std::string&& msg);
  explicit InvalidNumber(const char* msg);
};

class MPA_ERROR_EXPORT DivisionByZero : public std::domain_error {
 public:
  explicit DivisionByZero(const std::string& msg);
  explicit DivisionByZero(std::string&& msg);
  explicit DivisionByZero(const char* msg);
};

}  // namespace error
}  // namespace mpa

#endif  // MPA_MPERROR_INCLUDE_MPAEXCEPT_H_

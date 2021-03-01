#ifndef MPA_MPERROR_INCLUDE_MPAEXCEPT_H_
#define MPA_MPABASE_INCLUDE_MPAEXCEPT_H_

#include <stdexcept>

namespace mpa {
namespace error {

class InvalidArgument : public std::invalid_argument {
 public:
  explicit InvalidArgument(const std::string& msg);
  explicit InvalidArgument(std::string&& msg);
  explicit InvalidArgument(const char* msg);
};

class InvalidNumber : public std::logic_error {
 public:
  explicit InvalidNumber(const std::string& msg);
  explicit InvalidNumber(std::string&& msg);
  explicit InvalidNumber(const char* msg);
};

class DivisionByZero : public std::domain_error {
 public:
  explicit DivisionByZero(const std::string& msg);
  explicit DivisionByZero(std::string&& msg);
  explicit DivisionByZero(const char* msg);
};

}  // namespace error
}  // namespace mpa

#endif  // MPA_MPABASE_INCLUDE_MPAEXCEPT_H_

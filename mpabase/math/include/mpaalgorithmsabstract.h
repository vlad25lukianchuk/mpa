#ifndef MPA_MPABASE_MATH_INCLUDE_MPAOPERATIONSABSTRACT_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAOPERATIONSABSTRACT_H_

#include <string>

#include "mpanumber.h"

namespace mpa {
namespace math {
namespace impl {

class AlgorithmsAbstract {
 public:
  virtual ~AlgorithmsAbstract() = default;
  virtual core::Number Add(const std::string& lhs,
                           const std::string& rhs) const noexcept = 0;
  virtual core::Number Subtract(const std::string& lhs,
                                const std::string& rhs) const noexcept = 0;
  virtual core::Number Multiply(const std::string& lhs,
                                const std::string& rhs) const noexcept = 0;
  virtual core::Number Divide(const std::string& lhs,
                              const std::string& rhs) const noexcept = 0;
  virtual core::Number Reminder(const std::string& lhs,
                                const std::string& rhs) const noexcept = 0;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPAOPERATIONSABSTRACT_H_

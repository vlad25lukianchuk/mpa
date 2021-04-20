#ifndef MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSIMPLABSTRACT_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSIMPLABSTRACT_H_

#include <string>

namespace mpa {
namespace math {
namespace impl {

class AlgorithmsImplAbstract {
 public:
  virtual ~AlgorithmsImplAbstract() = default;
  virtual std::string Add(const std::string& lhs,
                          const std::string& rhs) const noexcept = 0;
  virtual std::string Subtract(const std::string& lhs,
                               const std::string& rhs) const noexcept = 0;
  virtual std::string Multiply(const std::string& lhs,
                               const std::string& rhs) const noexcept = 0;
  virtual std::string Divide(const std::string& lhs,
                             const std::string& rhs) const noexcept = 0;
  virtual std::string Reminder(const std::string& lhs,
                               const std::string& rhs) const noexcept = 0;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSIMPLABSTRACT_H_

#ifndef MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALGORITHMSIMPL_H_
#define MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALGORITHMSIMPL_H_

#include "mpaalgorithmsimplabstract.h"

namespace mpa {
namespace math {
namespace impl {

class StandardAlgorithmsImpl : public AlgorithmsImplAbstract {
 public:
  std::string Add(const std::string& lhs,
                  const std::string& rhs) const noexcept override;
  std::string Subtract(const std::string& lhs,
                       const std::string& rhs) const noexcept override;
  std::string Multiply(const std::string& lhs,
                       const std::string& rhs) const noexcept override;
  std::string Divide(const std::string& lhs,
                     const std::string& rhs) const noexcept override;
  std::string Reminder(const std::string& lhs,
                       const std::string& rhs) const noexcept override;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALGORITHMSIMPL_H_

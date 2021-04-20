#ifndef MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALTORITHMS_H_
#define MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALTORITHMS_H_

#include <memory>

#include "mpaalgorithmsabstract.h"
#include "mpaalgorithmsimplabstract.h"
#include "mpanumber.h"

namespace mpa {
namespace math {
namespace impl {

class StandardAlgorithms : public AlgorithmsAbstract {
 public:
  StandardAlgorithms();

  core::Number Add(const std::string& lhs,
                   const std::string& rhs) const noexcept override;
  core::Number Subtract(const std::string& lhs,
                        const std::string& rhs) const noexcept override;
  core::Number Multiply(const std::string& lhs,
                        const std::string& rhs) const noexcept override;
  core::Number Divide(const std::string& lhs,
                      const std::string& rhs) const noexcept override;
  core::Number Reminder(const std::string& lhs,
                        const std::string& rhs) const noexcept override;

 private:
  std::unique_ptr<AlgorithmsImplAbstract> impl_;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPASTANDARDALTORITHMS_H_

#ifndef MPA_MPABASE_MATH_INCLUDE_MPAMATH_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAMATH_H_

#include "mpamathglobal.h"
#include "mpanumber.h"

namespace mpa {
namespace math {

MPA_MATH_EXPORT core::Number Add(const core::Number& lhs,
                                 const core::Number& rhs) noexcept;
MPA_MATH_EXPORT core::Number Subtract(const core::Number& lhs,
                                      const core::Number& rhs) noexcept;
MPA_MATH_EXPORT core::Number Multiply(const core::Number& lhs,
                                      const core::Number& rhs) noexcept;
MPA_MATH_EXPORT core::Number Divide(const core::Number& lhs,
                                    const core::Number& rhs);
MPA_MATH_EXPORT core::Number Reminder(const core::Number& lhs,
                                      const core::Number& rhs);

}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MAHT_INCLUDE_MPAMATH_H_

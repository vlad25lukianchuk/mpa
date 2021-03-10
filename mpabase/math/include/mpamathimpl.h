#ifndef MPA_MPABASE_MATH_INCLUDE_MPAMATHIMPL_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAMATHIMPL_H_

#include <string>

#include "mpanumber.h"

namespace mpa {
namespace math {
namespace impl {

std::string AddImpl(const std::string& larger,
                    const std::string& smaller) noexcept;
std::string SubtractImpl(const std::string& lhs,
                         const std::string& rhs) noexcept;
std::string MultiplyImpl(const std::string& larger,
                         const std::string& smaller) noexcept;
std::string DivideImpl(const std::string& lhs, const std::string& rhs) noexcept;
std::string ReminderImpl(const std::string& lhs,
                         const std::string& rhs) noexcept;

inline core::Number Add(const std::string& lhs, const std::string& rhs) noexcept
{
  return lhs.size() > rhs.size() ? core::Number{AddImpl(lhs, rhs)}
                                 : core::Number{AddImpl(rhs, lhs)};
}

inline core::Number Subtract(const std::string& lhs,
                             const std::string& rhs) noexcept
{
  return core::IsAbsGreaterOrEqual(lhs, rhs)
             ? core::Number{SubtractImpl(lhs, rhs)}
             : -core::Number{SubtractImpl(rhs, lhs)};
}

inline core::Number Multiply(const std::string& lhs,
                             const std::string& rhs) noexcept
{
  return lhs.size() > rhs.size() ? core::Number{MultiplyImpl(lhs, rhs)}
                                 : core::Number{MultiplyImpl(rhs, lhs)};
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPAMATHIMPL_H_

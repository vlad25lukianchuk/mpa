#ifndef MPA_MPABASE_SRC_MPAMATH_H_
#define MPA_MPABASE_SRC_MPAMATH_H_

#include <string>

#include "mpanumber.h"

namespace mpa {
namespace math {

constexpr int kAsciiNumStart{48};

constexpr char ToChar(int num) noexcept
{
  return static_cast<char>(num + kAsciiNumStart);
}

constexpr int ToDec(char chr) noexcept
{
  return chr - kAsciiNumStart;
}

core::Number Add(const core::Number& lhs, const core::Number& rhs) noexcept;
core::Number Subtract(const core::Number& lhs,
                      const core::Number& rhs) noexcept;

namespace impl {

core::Number AddHelper(const core::Number& lhs,
                       const core::Number& rhs) noexcept;
core::Number SubtractHelper(const core::Number& lhs,
                            const core::Number& rhs) noexcept;

std::string AddImpl(const std::string& larger,
                    const std::string& smaller) noexcept;
std::string SubtractImpl(const std::string& lhs,
                         const std::string& rhs) noexcept;

}  // namespace impl

}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_SRC_MPAMATH_H_

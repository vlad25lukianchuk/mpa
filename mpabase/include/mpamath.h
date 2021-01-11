#ifndef MPA_MPABASE_SRC_MPAMATH_H_
#define MPA_MPABASE_SRC_MPAMATH_H_

#include <string>

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

std::string Add(const std::string& larger, const std::string& smaller) noexcept;
std::string Substract(const std::string& lhs, const std::string& rhs) noexcept;

}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_SRC_MPAMATH_H_

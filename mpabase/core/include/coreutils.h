#ifndef MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_
#define MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_

#include <string>

namespace mpa {
namespace core {

constexpr char kMinusChar{'-'};
constexpr char kPlusChar{'+'};

constexpr int kAsciiDigitStart{48};
constexpr int kAsciiDigitEnd{57};

constexpr int kBase{10}; // number representation (decimal)

constexpr char ToChar(int num) noexcept
{
  return static_cast<char>(num + kAsciiDigitStart);
}

constexpr int ToDec(char chr) noexcept
{
  return chr - kAsciiDigitStart;
}

constexpr bool IsDigit(char c) noexcept
{
  return c < kAsciiDigitStart || c > kAsciiDigitEnd;
}

bool IsAbsGreater(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsLess(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsGreaterOrEqual(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsLessOrEqual(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsEqual(const std::string& lhs, const std::string& rhs) noexcept;
bool IsNegative(const std::string& number) noexcept;
bool IsPositive(const std::string& number) noexcept;
bool HasNonDigitSymbol(const std::string& value) noexcept;

} // namespace core
} // namespace mpa

#endif // MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_

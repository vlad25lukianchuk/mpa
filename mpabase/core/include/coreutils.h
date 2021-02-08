#ifndef MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_
#define MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_

#include <string>

namespace mpa {
namespace core {

constexpr char kMinusChar{'-'};
constexpr char kPlusChar{'+'};

constexpr int kAsciiDigitStart{48};  // '0'
constexpr int kAsciiDigitEnd{57};    // '9';

constexpr int kBase{10};  // number representation (decimal)

constexpr bool IsDigit(char c) noexcept
{
  return kAsciiDigitStart <= c && kAsciiDigitEnd >= c;
}

constexpr bool IsDigit(int i) noexcept
{
  return 0 <= i && 9 >= i;
}

constexpr char ToChar(int num) noexcept
{
  // Does not check an input number
  // The caller should do the check of the result (via IsDigit)
  return static_cast<char>(num + kAsciiDigitStart);
}

constexpr int ToDec(char chr) noexcept
{
  // Does not perform any checks
  // The caller should do the check of the result (via IsDigit)
  return chr - kAsciiDigitStart;
}

bool IsAbsGreater(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsLess(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsGreaterOrEqual(const std::string& lhs,
                         const std::string& rhs) noexcept;
bool IsAbsLessOrEqual(const std::string& lhs, const std::string& rhs) noexcept;
bool IsAbsEqual(const std::string& lhs, const std::string& rhs) noexcept;
bool IsNegative(const std::string& number) noexcept;
bool IsPositive(const std::string& number) noexcept;
bool HasNonDigitSymbol(const std::string& value) noexcept;
bool HasPlusSignAtFront(const std::string& number) noexcept;

}  // namespace core
}  // namespace mpa

#endif  // MPA_MPABASE_CORE_INCLUDE_COREUTILS_H_

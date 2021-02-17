#include "mpacoreutils.h"

#include <algorithm>
#include <string>

namespace mpa {
namespace core {

using std::string;

bool IsAbsGreater(const string& lhs, const string& rhs) noexcept
{
  return lhs.size() == rhs.size() ? lhs > rhs : lhs.size() > rhs.size();
}

bool IsAbsLess(const string& lhs, const string& rhs) noexcept
{
  return lhs.size() == rhs.size() ? lhs < rhs : lhs.size() < rhs.size();
}

bool IsAbsGreaterOrEqual(const string& lhs, const string& rhs) noexcept
{
  return !IsAbsLess(lhs, rhs);
}

bool IsAbsLessOrEqual(const std::string& lhs, const std::string& rhs) noexcept
{
  return !IsAbsGreater(lhs, rhs);
}

bool IsAbsEqual(const std::string& lhs, const std::string& rhs) noexcept
{
  return rhs == lhs;
}

bool HasNonDigitSymbol(const string& value) noexcept
{
  return std::any_of(value.cbegin(), value.cend(), [](char c) {
    return c < kAsciiDigitStart || c > kAsciiDigitEnd;
  });
}

bool IsNegative(const string& number) noexcept
{
  return !number.empty() && number.front() == kMinusChar;
}

bool IsPositive(const string& number) noexcept
{
  return !number.empty() &&
         (number.front() == kPlusChar || IsDigit(number.front()));
}

bool HasPlusSignAtFront(const string& number) noexcept
{
  return !number.empty() && number.front() == kPlusChar;
}

void ClearLeadingZeroes(string& number) noexcept
{
  number.erase(number.begin(), std::find_if(number.begin(), number.end(),
                                            [](char c) { return '0' != c; }));
}

}  // namespace core
}  // namespace mpa

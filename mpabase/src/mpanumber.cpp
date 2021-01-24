#include "mpanumber.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "mpalog.h"

using std::string;

namespace mpa {
namespace core {

constexpr char kMinusChar{'-'};
constexpr char kPlusChar{'+'};

constexpr int kAsciiDigitStart{48};
constexpr int kAsciiDigitEnd{57};

Number::Number(std::string value, Sign sign) noexcept
    : value_{std::move(value)}, sign_{sign}
{
}

constexpr bool IsDigit(char c) noexcept
{
  return c < kAsciiDigitStart || c > kAsciiDigitEnd;
}

bool IsNegative(const string& number) noexcept
{
  return !number.empty() && number.front() == kMinusChar;
}

// TODO: mb redundant
bool IsPositive(const string& number) noexcept
{
  return !number.empty() &&
         (number.front() == kPlusChar || IsDigit(number.front()));
}

Number VerifyNumber(string&& number)
{
  // TODO: if empty, mb zero?
  // TODO: check trailing zeros
  if (number.empty()) {
    throw std::runtime_error{
        "The number value is empty, thus consider as not a number"};
  }

  Sign sign{Sign::kPlus};
  string value{std::move(number)};

  if (IsNegative(value)) {
    sign = Sign::kMinus;
    // unfortunate copy
    value = {value.cbegin() + 1, value.cend()};
  }

  if (HasNonDigitSymbol(value)) {
    std::ostringstream oss;
    oss << "Number: " << number << " contains non-digit symbols";
    throw std::runtime_error{oss.str()};
  }

  return Number{std::move(value), sign};
}

bool HasNonDigitSymbol(const string& value) noexcept
{
  return std::any_of(value.cbegin(), value.cend(), [](char c) {
    return c < kAsciiDigitStart || c > kAsciiDigitEnd;
  });
}

bool IsGreater(const string& lhs, const string& rhs) noexcept
{
  return lhs.size() == rhs.size() ? lhs > rhs : lhs.size() > rhs.size();
}

std::istream& operator>>(std::istream& ist, Number&)
{
  MPANotImplemented()
      << "std::istream &operator>>(std::istream &ist, Number& number)";
  return ist;
}

}  // namespace core
}  // namespace mpa

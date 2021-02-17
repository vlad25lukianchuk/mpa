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

Number::Number(std::string value, Sign sign) noexcept
    : value_{std::move(value)}, sign_{sign}
{
}

Number VerifyNumber(string&& number)
{
  if (number.empty()) {
    throw std::runtime_error{
        "The number value is empty, thus consider as not a number"};
  }

  Sign sign{Sign::kPlus};
  string value{std::move(number)};

  if (IsNegative(value)) {
    sign = Sign::kMinus;
    value.erase(value.cbegin());
  }

  // Values such as: 000-1234 are malformed
  // Values such as: -000123456 are acceptable. Leading zeroes (after minus)
  // are cleared
  ClearLeadingZeroes(value);

  if (value.empty()) {
    // number contains only zeroes, we trim it to just zero
    return Number{"0"};
  }

  if (HasNonDigitSymbol(value)) {
    std::ostringstream oss;
    oss << "Number: " << number << " contains non-digit symbols";
    throw std::runtime_error{oss.str()};
  }

  return Number{std::move(value), sign};
}

std::istream& operator>>(std::istream& ist, Number&)
{
  MPANotImplemented()
      << "std::istream &operator>>(std::istream &ist, Number& number)";
  return ist;
}

}  // namespace core
}  // namespace mpa

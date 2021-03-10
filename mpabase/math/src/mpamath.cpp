#include "mpamath.h"

#include "mpacoredefs.h"
#include "mpacoreutils.h"
#include "mpaexcept.h"
#include "mpamathimpl.h"
#include "mpanumber.h"

namespace mpa {
namespace math {

using mpa::core::IsAbsLess;
using mpa::core::Number;
using mpa::core::Sign;

Number Add(const Number& lhs, const Number& rhs) noexcept
{
  // Possible cases:
  // 1) The same sign positive: pure addition - result is positive
  // 2) The same sign negative: pure addition - result is negative
  // 3) Different signs: determine which is negative and perform subtraction

  if (lhs.sign() == rhs.sign()) {
    return lhs.sign() == Sign::kPlus ? impl::Add(lhs.value(), rhs.value())
                                     : -impl::Add(lhs.value(), rhs.value());
  }
  return lhs.sign() == Sign::kMinus ? impl::Subtract(rhs.value(), lhs.value())
                                    : impl::Subtract(lhs.value(), rhs.value());
}

Number Subtract(const Number& lhs, const Number& rhs) noexcept
{
  // Possible cases:
  // 1) The same sign positive: normal subtraction, result signess is based
  // on the number values
  // 2) The same sign negative: rhs becomes positive, than ordinary reversed
  // subtraction from 1)
  // 3) Different signs: if negative is lhs, than perform addition, result
  // is negative; if negative rhs, then perform addition, result is positive
  // 4) If equal: ZERO!!

  if (lhs.sign() == rhs.sign()) {
    return lhs.sign() == Sign::kPlus ? impl::Subtract(lhs.value(), rhs.value())
                                     : impl::Subtract(rhs.value(), lhs.value());
  }
  return lhs.sign() == Sign::kMinus ? -impl::Add(lhs.value(), rhs.value())
                                    : impl::Add(lhs.value(), rhs.value());
}

Number Multiply(const Number& lhs, const Number& rhs) noexcept
{
  // 1) Both positive - result is positive
  // 2) Both negative - result is positive
  // 3) Different signs - result is negative

  if (lhs == mpa::core::kZero || rhs == mpa::core::kZero) {
    return mpa::core::kZero;
  }

  return lhs.sign() == rhs.sign() ? impl::Multiply(lhs.value(), rhs.value())
                                  : -impl::Multiply(lhs.value(), rhs.value());
}

Number Divide(const Number& lhs, const Number& rhs)
{
  if (rhs == mpa::core::kZero) {
    throw mpa::error::DivisionByZero{
        "Operation not permitted: Division by zero."};
  }

  if (IsAbsLess(lhs.value(), rhs.value())) {
    return mpa::core::kZero;
  }

  return lhs.sign() == rhs.sign()
             ? Number{impl::DivideImpl(lhs.value(), rhs.value())}
             : -Number{impl::DivideImpl(lhs.value(), rhs.value())};
}

Number Reminder(const Number& lhs, const Number& rhs)
{
  if (rhs == mpa::core::kZero) {
    throw mpa::error::DivisionByZero{
        "Operation not permitted: Division (reminder) by zero."};
  }

  if (IsAbsLess(lhs.value(), rhs.value())) {
    return lhs;
  }

  return lhs.sign() == rhs.sign()
             ? Number{impl::ReminderImpl(lhs.value(), rhs.value())}
             : -Number{impl::ReminderImpl(lhs.value(), rhs.value())};
}

}  // namespace math
}  // namespace mpa

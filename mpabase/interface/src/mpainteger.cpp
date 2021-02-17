#include "mpainteger.h"

#include <string>
#include <utility>

#include "mpacoredefs.h"
#include "mpamath.h"
#include "mpanumber.h"

namespace mpa {

Integer::Integer(std::string number)
    : number_{core::VerifyNumber(std::move(number))}
{
}

Integer::Integer(core::Number&& number) noexcept : number_{number} {}

Integer& Integer::operator+=(const Integer& rhs) noexcept
{
  number_ = mpa::math::Add(number_, rhs.number_);
  return *this;
}

Integer& Integer::operator-=(const Integer& rhs) noexcept
{
  number_ = mpa::math::Subtract(number_, rhs.number_);
  return *this;
}

Integer& Integer::operator*=(const Integer& rhs) noexcept
{
  number_ = mpa::math::Multiply(number_, rhs.number_);
  return *this;
}

Integer& Integer::operator/=(const Integer& rhs)
{
  // TODO: mb handle exception?
  number_ = mpa::math::Divide(number_, rhs.number_);
  return *this;
}

Integer& Integer::operator%=(const Integer& rhs)
{
  // TODO: mb handle exception?
  number_ = mpa::math::Reminder(number_, rhs.number_);
  return *this;
}

Integer& Integer::operator++() noexcept
{
  number_ = mpa::math::Add(number_, mpa::core::kOne);
  return *this;
}

Integer& Integer::operator--() noexcept
{
  number_ = mpa::math::Subtract(number_, mpa::core::kOne);
  return *this;
}

}  // namespace mpa

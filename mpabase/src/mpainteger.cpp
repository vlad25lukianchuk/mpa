#include "mpainteger.h"

#include <iostream>
#include <string>
#include <utility>

#include "mpalog.h"
#include "mpamath.h"
#include "mpanumber.h"

using std::string;

namespace mpa {

Integer::Integer(string number) : number_{core::CheckNumber(std::move(number))}
{
}

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

Integer& Integer::operator*=(const Integer&) noexcept
{
  MPANotImplemented() << "Integer::operator*=" << std::endl;
  return *this;
}

Integer& Integer::operator/=(const Integer&)
{
  MPANotImplemented() << "Integer::operator/=" << std::endl;
  return *this;
}

Integer& Integer::operator%=(const Integer&)
{
  MPANotImplemented() << "Integer::operator%=" << std::endl;
  return *this;
}

Integer& Integer::operator++() noexcept
{
  MPANotImplemented() << "Integer::operator++()" << std::endl;
  //TODO: NUMERIC 1!
  return *this;
}

Integer& Integer::operator--() noexcept
{
  MPANotImplemented() << "Integer::operator--()" << std::endl;
  return *this;
}

std::istream& operator>>(std::istream& ist, Integer&)
{
  MPANotImplemented() << "Integer::operator>>" << std::endl;
  return ist;
}

}  // namespace mpa

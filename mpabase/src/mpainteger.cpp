#include "mpainteger.h"

#include <iostream>
#include <string>
#include <utility>

#include "mpalog.h"
#include "mpamath.h"

using std::string;

namespace mpa {

Integer::Integer(string number) : number_{std::move(number)}
{
  // TODO: check signess?
}

Integer& Integer::operator+=(const Integer& rhs) noexcept
{
  if (number_.size() > rhs.Value().size()) {
    number_ = mpa::math::Add(number_, rhs.Value());
  } else {
    number_ = mpa::math::Add(rhs.Value(), number_);
  }
  return *this;
}

Integer& Integer::operator-=(const Integer&) noexcept
{
  // 1) -a-a;
  // 2)  a-b;
  // 3) -a - -b = -a + b = b - a
  // 4) a - - a = a + a
  MPANotImplemented() << "Integer::operator-=" << std::endl;
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

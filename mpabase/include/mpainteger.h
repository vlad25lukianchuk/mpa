#ifndef MPA_MPABASE_SRC_MPAINTEGER_H_
#define MPA_MPABASE_SRC_MPAINTEGER_H_

#include <iostream>
#include <string>

#include "mpanumber.h"

namespace mpa {

class Integer {
 public:
  // TODO: Any other ctrs?
  explicit Integer(std::string number);

  Integer& operator+=(const Integer& rhs) noexcept;
  Integer& operator-=(const Integer& rhs) noexcept;
  Integer& operator*=(const Integer& rhs) noexcept;
  Integer& operator/=(const Integer& rhs);
  Integer& operator%=(const Integer& rhs);

  Integer& operator++() noexcept;
  Integer& operator--() noexcept;

  // TODO: unary minus, unary plus, conversion operators?
  // comparison operators, etc. a lot of TODO.

  friend std::ostream& operator<<(std::ostream& ost, const Integer& number);

 private:
  core::Number number_;
};

inline Integer operator+(Integer lhs, const Integer& rhs) noexcept
{
  return lhs += rhs;
}

inline Integer operator-(Integer lhs, const Integer& rhs) noexcept
{
  return lhs -= rhs;
}

inline Integer operator*(Integer lhs, const Integer& rhs) noexcept
{
  return lhs *= rhs;
}

inline Integer operator/(Integer lhs, const Integer& rhs)
{
  return lhs /= rhs;
}

inline Integer operator%(Integer lhs, const Integer& rhs)
{
  return lhs %= rhs;
}

inline Integer operator++(Integer& lhs, int) noexcept
{
  Integer tmp{lhs};
  ++lhs;
  return tmp;
}

inline Integer operator--(Integer& lhs, int) noexcept
{
  Integer tmp{lhs};
  --lhs;
  return tmp;
}

inline std::ostream& operator<<(std::ostream& ost, const Integer& number)
{
  return ost << number.number_;
}

std::istream& operator>>(std::istream& ist, Integer& number);

}  // namespace mpa

#endif  // MPA_MPABASE_SRC_MPAINTEGER_H_

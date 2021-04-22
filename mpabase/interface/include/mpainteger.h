#ifndef MPA_MPABASE_INTERFACE_INCLUDE_MPAINTEGER_H_
#define MPA_MPABASE_INTERFACE_INCLUDE_MPAINTEGER_H_

#include <iostream>
#include <string>

#include "mpainterfaceglobal.h"
#include "mpanumber.h"

namespace mpa {

class MPA_INTERFACE_EXPORT Integer {
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

  friend MPA_INTERFACE_EXPORT Integer operator-(const Integer&) noexcept;
  friend MPA_INTERFACE_EXPORT bool operator==(const Integer& lhs,
                                              const Integer& rhs) noexcept;
  friend MPA_INTERFACE_EXPORT bool operator>(const Integer& lhs,
                                             const Integer& rhs) noexcept;
  friend MPA_INTERFACE_EXPORT bool operator<(const Integer& ohs,
                                             const Integer& rhs) noexcept;

  friend MPA_INTERFACE_EXPORT std::ostream& operator<<(std::ostream& ost,
                                                       const Integer& number);
  friend MPA_INTERFACE_EXPORT std::istream& operator>>(std::istream& ost,
                                                       Integer& number);

  // TODO: conversion, literal operators?

 private:
  explicit Integer(core::Number&& number) noexcept;
  core::Number number_;
};

MPA_INTERFACE_EXPORT inline Integer operator+(Integer lhs,
                                              const Integer& rhs) noexcept
{
  return lhs += rhs;
}

MPA_INTERFACE_EXPORT inline Integer operator-(Integer lhs,
                                              const Integer& rhs) noexcept
{
  return lhs -= rhs;
}

MPA_INTERFACE_EXPORT inline Integer operator*(Integer lhs,
                                              const Integer& rhs) noexcept
{
  return lhs *= rhs;
}

MPA_INTERFACE_EXPORT inline Integer operator/(Integer lhs, const Integer& rhs)
{
  return lhs /= rhs;
}

MPA_INTERFACE_EXPORT inline Integer operator%(Integer lhs, const Integer& rhs)
{
  return lhs %= rhs;
}

MPA_INTERFACE_EXPORT inline Integer operator++(Integer& lhs, int) noexcept
{
  Integer tmp{lhs};
  ++lhs;
  return tmp;
}

MPA_INTERFACE_EXPORT inline Integer operator--(Integer& lhs, int) noexcept
{
  Integer tmp{lhs};
  --lhs;
  return tmp;
}

MPA_INTERFACE_EXPORT inline Integer operator-(const Integer& rhs) noexcept
{
  return Integer{-rhs.number_};
}

MPA_INTERFACE_EXPORT inline Integer operator+(const Integer& rhs) noexcept
{
  return rhs;
}

MPA_INTERFACE_EXPORT inline bool operator==(const Integer& lhs,
                                            const Integer& rhs) noexcept
{
  return lhs.number_ == rhs.number_;
}

MPA_INTERFACE_EXPORT inline bool operator!=(const Integer& lhs,
                                            const Integer& rhs) noexcept
{
  return !(lhs == rhs);
}

MPA_INTERFACE_EXPORT inline bool operator>(const Integer& lhs,
                                           const Integer& rhs) noexcept
{
  return lhs.number_ > rhs.number_;
}

MPA_INTERFACE_EXPORT inline bool operator<(const Integer& lhs,
                                           const Integer& rhs) noexcept
{
  return lhs.number_ < rhs.number_;
}

MPA_INTERFACE_EXPORT inline bool operator>=(const Integer& lhs,
                                            const Integer& rhs) noexcept
{
  return !(lhs < rhs);
}

MPA_INTERFACE_EXPORT inline bool operator<=(const Integer& lhs,
                                            const Integer& rhs) noexcept
{
  return !(lhs > rhs);
}

MPA_INTERFACE_EXPORT inline std::ostream& operator<<(std::ostream& ost,
                                                     const Integer& number)
{
  return ost << number.number_;
}

MPA_INTERFACE_EXPORT inline std::istream& operator>>(std::istream& ist,
                                                     Integer& number)
{
  return ist >> number.number_;
}

}  // namespace mpa

#endif  // MPA_MPABASE_INTERFACE_INCLUDE_MPAINTEGER_H_

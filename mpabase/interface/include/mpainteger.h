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

  friend Integer operator-(const Integer&) noexcept;
  friend bool operator==(const Integer& lhs, const Integer& rhs) noexcept;
  friend bool operator>(const Integer& lhs, const Integer& rhs) noexcept;
  friend bool operator<(const Integer& ohs, const Integer& rhs) noexcept;

  friend std::ostream& operator<<(std::ostream& ost, const Integer& number);
  friend std::istream& operator>>(std::istream& ost, Integer& number);

  // TODO: conversion, literal operators?

 private:
  explicit Integer(core::Number&& number) noexcept;
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

inline Integer operator-(const Integer& rhs) noexcept
{
  return Integer{-rhs.number_};
}

inline Integer operator+(const Integer& rhs) noexcept
{
  return rhs;
}

inline bool operator==(const Integer& lhs, const Integer& rhs) noexcept
{
  return lhs.number_ == rhs.number_;
}

inline bool operator!=(const Integer& lhs, const Integer& rhs) noexcept
{
  return !(lhs == rhs);
}

inline bool operator>(const Integer& lhs, const Integer& rhs) noexcept
{
  return lhs.number_ > rhs.number_;
}

inline bool operator<(const Integer& lhs, const Integer& rhs) noexcept
{
  return lhs.number_ < rhs.number_;
}

inline bool operator>=(const Integer& lhs, const Integer& rhs) noexcept
{
  return !(lhs < rhs);
}

inline bool operator<=(const Integer& lhs, const Integer& rhs) noexcept
{
  return !(lhs > rhs);
}

inline std::ostream& operator<<(std::ostream& ost, const Integer& number)
{
  return ost << number.number_;
}

inline std::istream& operator>>(std::istream& ist, Integer& number)
{
  return ist >> number.number_;
}

}  // namespace mpa

#endif  // MPA_MPABASE_SRC_MPAINTEGER_H_

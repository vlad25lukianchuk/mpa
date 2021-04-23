#ifndef MPA_MPABASE_CORE_INCLUDE_MPANUMBER_H_
#define MPA_MPABASE_CORE_INCLUDE_MPANUMBER_H_

#include <iostream>
#include <string>
#include <utility>

#include "mpacoreglobal.h"
#include "mpacoreutils.h"

namespace mpa {
namespace core {

enum class MPA_CORE_EXPORT Sign { kPlus, kMinus };

class MPA_CORE_EXPORT Number {
 public:
  Number() noexcept = default;
  explicit Number(std::string value, Sign sign = Sign::kPlus) noexcept;

  const std::string& value() const noexcept { return value_; }
  constexpr Sign sign() const noexcept { return sign_; }

  friend MPA_CORE_EXPORT Number operator-(const Number&) noexcept;
  friend MPA_CORE_EXPORT Number operator-(Number&&) noexcept;
  friend MPA_CORE_EXPORT bool operator==(const Number&, const Number&) noexcept;
  friend MPA_CORE_EXPORT bool operator>(const Number&, const Number&) noexcept;
  friend MPA_CORE_EXPORT bool operator<(const Number&, const Number&) noexcept;
  friend MPA_CORE_EXPORT std::ostream& operator<<(std::ostream&, const Number&);
  friend MPA_CORE_EXPORT std::istream& operator>>(std::istream&, Number&);

 private:
  std::string value_;
  Sign sign_{Sign::kPlus};
};

MPA_CORE_EXPORT Number VerifyNumber(std::string&& number);

MPA_CORE_EXPORT inline Number operator-(const Number& rhs) noexcept
{
  return rhs.sign_ == Sign::kMinus ? Number{rhs.value_, Sign::kPlus}
                                   : Number{rhs.value_, Sign::kMinus};
}

MPA_CORE_EXPORT inline Number operator-(Number&& rhs) noexcept
{
  Number tmp;
  std::swap(tmp, rhs);
  tmp.sign_ = tmp.sign_ == Sign::kMinus ? Sign::kPlus : Sign::kMinus;
  return tmp;
}

MPA_CORE_EXPORT inline Number operator+(const Number& rhs) noexcept
{
  return rhs;
}

MPA_CORE_EXPORT inline bool operator==(const Number& lhs,
                                       const Number& rhs) noexcept
{
  return lhs.sign_ == rhs.sign_ && lhs.value_ == rhs.value_;
}

MPA_CORE_EXPORT inline bool operator!=(const Number& lhs,
                                       const Number& rhs) noexcept
{
  return !(lhs == rhs);
}

MPA_CORE_EXPORT inline bool operator>(const Number& lhs,
                                      const Number& rhs) noexcept
{
  // 1) Sign - positive always is greater than negative
  // 2) If the same sign - compare values, in case of negative values
  // the comparison logic is inverse
  return lhs.sign_ == rhs.sign_ ? (lhs.sign_ == Sign::kMinus
                                       ? IsAbsGreater(rhs.value_, lhs.value_)
                                       : IsAbsGreater(lhs.value_, rhs.value_))
                                : lhs.sign_ == Sign::kPlus;
}

MPA_CORE_EXPORT inline bool operator<(const Number& lhs,
                                      const Number& rhs) noexcept
{
  return lhs.sign_ == rhs.sign_ ? (lhs.sign_ == Sign::kMinus
                                       ? IsAbsGreater(lhs.value_, rhs.value_)
                                       : IsAbsGreater(rhs.value_, lhs.value_))
                                : lhs.sign_ == Sign::kMinus;
}

MPA_CORE_EXPORT inline bool operator>=(const Number& lhs,
                                       const Number& rhs) noexcept
{
  return !(lhs < rhs);
}

MPA_CORE_EXPORT inline bool operator<=(const Number& lhs,
                                       const Number& rhs) noexcept
{
  return !(lhs > rhs);
}

MPA_CORE_EXPORT inline std::ostream& operator<<(std::ostream& ost,
                                                const Number& number)
{
  return number.sign_ == Sign::kMinus ? ost << '-' << number.value_
                                      : ost << number.value_;
}

MPA_CORE_EXPORT std::istream& operator>>(std::istream& ist, Number&);

}  // namespace core
}  // namespace mpa

#endif  // MPA_MPABASE_CORE_INCLUDE_MPANUMBER_H_

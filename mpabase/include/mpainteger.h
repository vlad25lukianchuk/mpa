#ifndef MPA_MPABASE_SRC_MPAINTEGER_H_
#define MPA_MPABASE_SRC_MPAINTEGER_H_

#include <iostream>
#include <string>

namespace mpa {

enum class Sign { kPlus, kMinus };

class Integer {
 public:
  // TODO: Any other ctrs?
  // 1) do we need implicit conversion?
  // 2) do we need ctr's from the const char*?
  // 3) to think about sign representation
  explicit Integer(std::string number);
  const std::string& Value() const noexcept { return number_; }

  Integer& operator+=(const Integer& rhs) noexcept;
  Integer& operator-=(const Integer& rhs) noexcept;
  Integer& operator*=(const Integer& rhs) noexcept;
  Integer& operator/=(const Integer& rhs);
  Integer& operator%=(const Integer& rhs);

  Integer& operator++() noexcept;
  Integer& operator--() noexcept;

 private:
  std::string number_;
  Sign sign_{Sign::kPlus};
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

Integer operator--(Integer& lhs, int) noexcept
{
  Integer tmp{lhs};
  --lhs;
  return tmp;
}

inline std::ostream& operator<<(std::ostream& ost, const Integer& number)
{
  return ost << number.Value();
}

std::istream& operator>>(std::istream& ist, Integer& number);

}  // namespace mpa

#endif  // MPA_MPABASE_SRC_MPAINTEGER_H_

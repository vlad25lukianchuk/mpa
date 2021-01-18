#include "mpamath.h"

#include "mpanumber.h"

using mpa::core::Number;
using std::string;

namespace mpa {
namespace math {

constexpr int kBase{10};

Number Add(const Number& lhs, const Number& rhs) noexcept
{
  // Possible cases:
  // 1) The same sign positive: pure addition - result is positive
  // 2) The same sign negative: pure addition - result is negative
  // 3) Different signs: determine which is negative and perform subtraction

  if (lhs.sign() == rhs.sign()) {
    return lhs.sign() == mpa::core::Sign::kPlus ? impl::AddHelper(lhs, rhs)
                                                : -impl::AddHelper(lhs, rhs);
  }
  return lhs.sign() == mpa::core::Sign::kMinus ? impl::SubtractHelper(rhs, lhs)
                                               : impl::SubtractHelper(lhs, rhs);
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
    return lhs.sign() == mpa::core::Sign::kPlus
               ? impl::SubtractHelper(lhs, rhs)
               : impl::SubtractHelper(rhs, lhs);
  }
  return lhs.sign() == mpa::core::Sign::kMinus ? -impl::AddHelper(lhs, rhs)
                                               : impl::AddHelper(lhs, rhs);
}

namespace impl {

Number AddHelper(const Number& lhs, const Number& rhs) noexcept
{
  if (lhs.value().size() > rhs.value().size()) {
    return Number{AddImpl(lhs.value(), rhs.value())};
  }
  return Number{AddImpl(rhs.value(), lhs.value())};
}

core::Number SubtractHelper(const core::Number& lhs,
                            const core::Number& rhs) noexcept
{
  return core::IsGreater(lhs.value(), rhs.value()) ?
                                                   Number{SubtractImpl(lhs.value(), rhs.value())}
                                                   : -Number{SubtractImpl(rhs.value(), lhs.value())};
}

// TODO: works, but not quite elegant
string AddImpl(const string& larger, const string& smaller) noexcept
{
  string reverse_res;
  reverse_res.reserve(larger.size());

  auto s_it = smaller.rbegin();
  int increaser{0};

  for (auto l_it = larger.rbegin(); l_it != larger.rend(); ++l_it) {
    const int base = ToDec(*l_it) + increaser;
    const int addition = s_it != smaller.rend() ? ToDec(*s_it++) : 0;
    const int res = (base + addition) < kBase
                        ? (increaser = 0, base + addition)
                        : (increaser = 1, base + addition - kBase);
    reverse_res.push_back(ToChar(res));
  }

  // add additional 'one' at the end if needed
  if (increaser) {
    reverse_res.push_back('1');
  }

  return {reverse_res.rbegin(), reverse_res.rend()};
}

string SubtractImpl(const string& larger, const string& smaller) noexcept
{
  string reverse_res;

  auto s_it = smaller.rbegin();
  int reducer{0};

  for (auto l_it = larger.rbegin(); l_it != larger.rend(); ++l_it) {
    const int subtractor = ToDec(*l_it) - reducer;
    const int subtracted = s_it != smaller.rend() ? ToDec(*s_it++) : 0;
    const int res = subtractor >= subtracted
                        ? (reducer = 0, subtractor - subtracted)
                        : (reducer = 1, subtractor + kBase - subtracted);
    reverse_res.push_back(ToChar(res));
  }

  // skip trailing zeroes at the end
  auto r_it = reverse_res.rbegin();
  while (*r_it == '0') {
    ++r_it;
  }

  return {r_it, reverse_res.rend()};
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

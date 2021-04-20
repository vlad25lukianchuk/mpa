#include "mpastandardalgorithmsimpl.h"

#include <string>
#include <vector>

#include "mpacoreutils.h"

namespace mpa {
namespace math {
namespace impl {

using mpa::core::IsAbsGreaterOrEqual;
using mpa::core::kBase;
using mpa::core::ToChar;
using mpa::core::ToDec;

std::string StandardAlgorithmsImpl::Add(const std::string& lhs,
                                        const std::string& rhs) const noexcept
{
  // consider lhs is larger number than rhs
  std::string reverse_res;
  reverse_res.reserve(lhs.size());

  auto s_it = rhs.rbegin();
  int carry{0};

  for (auto l_it = lhs.rbegin(); l_it != lhs.rend(); ++l_it) {
    const int base = ToDec(*l_it) + carry;
    const int addition = s_it != rhs.rend() ? ToDec(*s_it++) : 0;
    const int res = (base + addition) < kBase
                        ? (carry = 0, base + addition)
                        : (carry = 1, base + addition - kBase);
    reverse_res.push_back(ToChar(res));
  }

  // add additional 'one' at the end if needed
  if (carry) {
    reverse_res.push_back('1');
  }

  return {reverse_res.rbegin(), reverse_res.rend()};
}

std::string StandardAlgorithmsImpl::Subtract(
    const std::string& lhs, const std::string& rhs) const noexcept
{
  // consider lhs is larger than rhs
  std::string reverse_res;

  auto s_it = rhs.rbegin();
  int borrow{0};

  for (auto l_it = lhs.rbegin(); l_it != lhs.rend(); ++l_it) {
    const int subtractor = ToDec(*l_it) - borrow;
    const int subtracted = s_it != rhs.rend() ? ToDec(*s_it++) : 0;
    const int res = subtractor >= subtracted
                        ? (borrow = 0, subtractor - subtracted)
                        : (borrow = 1, subtractor + kBase - subtracted);
    reverse_res.push_back(ToChar(res));
  }

  // skip trailing zeroes at the end
  auto r_it = reverse_res.rbegin();
  while (r_it != reverse_res.rend() && *r_it == '0') {
    ++r_it;
  }

  if (r_it == reverse_res.rend()) {
    return "0";
  }

  return {r_it, reverse_res.rend()};
}

std::string StandardAlgorithmsImpl::Multiply(
    const std::string& lhs, const std::string& rhs) const noexcept
{
  // consider lhs is larger than rhs
  std::vector<std::string> additions;
  additions.reserve(rhs.size());

  int counter{0};

  // O(n*n)
  for (auto s_it = rhs.rbegin(); s_it != rhs.rend(); ++s_it) {
    const int multiplier = ToDec(*s_it);
    std::string tmp_res;
    int carry{0};
    for (auto l_it = lhs.rbegin(); l_it != lhs.rend(); ++l_it) {
      const int res = ToDec(*l_it) * multiplier + carry;
      const int reminder =
          res < kBase ? (carry = 0, res) : (carry = res / kBase, res % kBase);
      tmp_res.push_back(ToChar(reminder));
    }

    if (carry) {
      tmp_res.push_back(ToChar(carry));
    }

    // Too bad, reverse and add additional zeroes at the end
    // for each addition starting from second (counter == 1)
    tmp_res = {tmp_res.rbegin(), tmp_res.rend()};
    for (int i = 0; i < counter; ++i) {
      tmp_res.push_back('0');
    }

    additions.push_back(std::move(tmp_res));
    ++counter;
  }

  std::string res{additions[0]};
  for (size_t i = 1; i < additions.size(); ++i) {
    res = Add(additions[i], res);
  }

  return res;
}

std::string StandardAlgorithmsImpl::Divide(
    const std::string& lhs, const std::string& rhs) const noexcept
{
  std::string res;

  // 1) find the fist number in lhs - lhs0 which is greter than of equal to rhs
  // 2) subtract from lhs0 rhs: rest = lhs0 - rhs. Continue untill rest > rhs
  // 3) number of subtractions is the fist digit in result
  // 4) concatenate rest with the next digit from lhs and continue 2)-3)
  // till lhs has digits.
  // 5) Discard rest if any

  auto l_it = lhs.begin();
  std::string lhs0;

  // Find the first number in lhs which is greater than or equal to rhs
  while (l_it != lhs.end() && !IsAbsGreaterOrEqual(lhs0, rhs)) {
    lhs0 += *l_it++;
  }

  while (true) {
    // Find result
    int subtraction_count{0};
    while (IsAbsGreaterOrEqual(lhs0, rhs)) {
      lhs0 = Subtract(lhs0, rhs);
      ++subtraction_count;
    }
    // clear, if we do not have reminder
    if (lhs0 == "0") {
      lhs0.clear();
    }
    res.push_back(ToChar(subtraction_count));

    if (l_it == lhs.end()) {
      break;
    }

    // add the next digit
    lhs0 += *l_it++;
  }

  return res;
}

std::string StandardAlgorithmsImpl::Reminder(
    const std::string& lhs, const std::string& rhs) const noexcept
{
  // Currently just copy-paste division implementation with
  // some adjustments
  auto l_it = lhs.begin();
  std::string lhs0;
  while (l_it != lhs.end()) {
    if (lhs0 == "0") {
      lhs0.clear();
    }
    while (l_it != lhs.end() && !IsAbsGreaterOrEqual(lhs0, rhs)) {
      lhs0 += *l_it++;
    }
    while (IsAbsGreaterOrEqual(lhs0, rhs)) {
      lhs0 = Subtract(lhs0, rhs);
    }
  }
  return lhs0;
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

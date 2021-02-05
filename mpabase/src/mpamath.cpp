#include "mpamath.h"

#include <stdexcept>
#include <string>
#include <vector>

#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using std::string;
using std::vector;

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
    return lhs.sign() == Sign::kPlus ? impl::AddHelper(lhs, rhs)
                                     : -impl::AddHelper(lhs, rhs);
  }
  return lhs.sign() == Sign::kMinus ? impl::SubtractHelper(rhs, lhs)
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
    return lhs.sign() == Sign::kPlus ? impl::SubtractHelper(lhs, rhs)
                                     : impl::SubtractHelper(rhs, lhs);
  }
  return lhs.sign() == Sign::kMinus ? -impl::AddHelper(lhs, rhs)
                                    : impl::AddHelper(lhs, rhs);
}

Number Multiply(const Number& lhs, const Number& rhs) noexcept
{
  // 1) Both positive - result is positive
  // 2) Both negative - result is positive
  // 3) Different signs - result is negative
  return lhs.sign() == rhs.sign() ? impl::MultiplyHelper(lhs, rhs)
                                  : -impl::MultiplyHelper(lhs, rhs);
}

Number Divide(const Number& lhs, const Number& rhs)
{
  if (rhs.value() == "0" || rhs.value() == "-0" || rhs.value() == "+0") {
    throw std::runtime_error{"Operation not permitted: Division by zero."};
  }

  if (lhs.value().size() < rhs.value().size() ||
      (lhs.value().size() == rhs.value().size() && lhs.value() < rhs.value())) {
    // ZERO AGAIN
    return Number{"0"};
  }

  return lhs.sign() == rhs.sign()
             ? Number{impl::DivideImpl(lhs.value(), rhs.value())}
             : -Number{impl::DivideImpl(lhs.value(), rhs.value())};
}

core::Number Reminder(const core::Number& lhs, const core::Number& rhs)
{
  if (rhs.value() == "0" || rhs.value() == "-0" || rhs.value() == "+0") {
    throw std::runtime_error{
        "Operation not permitted: Division (reminder) by zero."};
  }

  if (lhs.value().size() < rhs.value().size() ||
      (lhs.value().size() == rhs.value().size() && lhs.value() < rhs.value())) {
    return rhs;
  }

  return lhs.sign() == rhs.sign()
             ? Number{impl::ReminderImpl(lhs.value(), rhs.value())}
             : -Number{impl::ReminderImpl(lhs.value(), rhs.value())};
}

namespace impl {

Number AddHelper(const Number& lhs, const Number& rhs) noexcept
{
  return lhs.value().size() > rhs.value().size()
             ? Number{AddImpl(lhs.value(), rhs.value())}
             : Number{AddImpl(rhs.value(), lhs.value())};
}

Number SubtractHelper(const core::Number& lhs, const core::Number& rhs) noexcept
{
  return core::IsGreater(lhs.value(), rhs.value())
             ? Number{SubtractImpl(lhs.value(), rhs.value())}
             : -Number{SubtractImpl(rhs.value(), lhs.value())};
}

// TODO: multiplication by zero does not work properly
// (it results in many zeroes instead of one)
Number MultiplyHelper(const Number& lhs, const Number& rhs) noexcept
{
  // if we multiply larger by smaller, the number of additions is less
  // (equal to the number of digits in smaller)
  return lhs.value().size() > rhs.value().size()
             ? Number{MultiplyImpl(lhs.value(), rhs.value())}
             : Number{MultiplyImpl(rhs.value(), lhs.value())};
}

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

string MultiplyImpl(const string& larger, const string& smaller) noexcept
{
  vector<string> additions;
  additions.reserve(smaller.size());

  int increaser{0};
  int counter{0};

  // O(n*n)
  for (auto s_it = smaller.rbegin(); s_it != smaller.rend(); ++s_it) {
    const int multiplier = ToDec(*s_it);
    string tmp_res;
    for (auto l_it = larger.rbegin(); l_it != larger.rend(); ++l_it) {
      const int res = ToDec(*l_it) * multiplier + increaser;
      const int reminder = res < kBase ? (increaser = 0, res)
                                       : (increaser = res / kBase, res % kBase);
      tmp_res.push_back(ToChar(reminder));
    }

    if (increaser) {
      tmp_res.push_back(ToChar(increaser));
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

  string res{additions[0]};
  for (size_t i = 1; i < additions.size(); ++i) {
    res = AddImpl(additions[i], res);
  }

  return res;
}

// TODO: TO UTILS!!!
bool IsLess(const std::string& lhs, const std::string& rhs) noexcept
{
  return lhs.size() == rhs.size() ? lhs < rhs : lhs.size() < rhs.size();
}

bool IsGreaterOrEqual(const std::string& lhs, const std::string& rhs) noexcept
{
  return !IsLess(lhs, rhs);
}

string DivideImpl(const string& lhs, const string& rhs) noexcept
{
  string res;

  // 1) find the fist number in lhs - lhs0 which is greter than rhs
  // 2) subtract from lhs0 rhs: rest = lhs0 - rhs. Continue untill rest > rhs
  // 3) number of subtactions is the fist digit in result
  // 4) concatenate rest with the next digit from lhs and continue 1)-3)
  // till lhs has digits.
  // 5) Discard rest if any

  auto l_it = lhs.begin();
  string lhs0;

  // UGLY
  while (l_it != lhs.end() && !IsGreaterOrEqual(lhs0, rhs)) {
    lhs0 += *l_it++;
  }

  while (l_it != lhs.end()) {
    if (lhs0.empty()) {
      while (l_it != lhs.end() && !IsGreaterOrEqual(lhs0, rhs)) {
        lhs0 += *l_it++;
        res.push_back('0');
      }
    } else {
      while (l_it != lhs.end() && !IsGreaterOrEqual(lhs0, rhs)) {
        lhs0 += *l_it++;
      }
    }
    int counter{0};
    while (IsGreaterOrEqual(lhs0, rhs)) {
      lhs0 = SubtractImpl(lhs0, rhs);
      ++counter;
    }
    if (counter) {
      res.push_back(ToChar(counter));
    }
  }
  return res;
}

string ReminderImpl(const string& lhs, const string& rhs) noexcept
{
  // Currently just copy-paste division implementation with
  // some adjustments
  auto l_it = lhs.begin();
  string lhs0;
  while (l_it != lhs.end()) {
    while (l_it != lhs.end() && !IsGreaterOrEqual(lhs0, rhs)) {
      lhs0 += *l_it++;
    }
    while (IsGreaterOrEqual(lhs0, rhs)) {
      lhs0 = SubtractImpl(lhs0, rhs);
    }
  }
  return lhs0.empty() ? "0" : lhs0;
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

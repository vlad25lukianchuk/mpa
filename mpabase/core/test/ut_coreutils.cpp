#include <gtest/gtest.h>

#include <array>
#include <cctype>
#include <iostream>

#include "mpacoreutils.h"

namespace char_interface {

constexpr std::array<char, 10> digits{'0', '1', '2', '3', '4',
                                      '5', '6', '7', '8', '9'};
// Silence warning (int and unsigned long comparison)
constexpr int digits_size = digits.size();

constexpr std::array<char, 10> not_digits{'a', '!', '#', '$', -100,
                                          '%', 'A', '*', '/', '\\'};
constexpr int not_digits_size = not_digits.size();

}  // namespace char_interface

namespace int_interface {

constexpr std::array<int, 10> digits{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

constexpr std::array<int, 6> not_digits{10, -2, 0x33, 1 << 4, 10000, -100};
constexpr int not_digits_size = not_digits.size();

}  // namespace int_interface

TEST(MpaCoreUtils, IsDigit_ValidCharInput)
{
  using char_interface::digits;
  for (auto d : digits) {
    EXPECT_TRUE(mpa::core::IsDigit(d));
  }
}

TEST(MpaCoreUtils, IsDigit_InvalidCharInput)
{
  using char_interface::not_digits;
  for (auto d : not_digits) {
    EXPECT_FALSE(mpa::core::IsDigit(d));
  }
}

TEST(MpaCoreUtils, IsDigit_ValidIntInput)
{
  using int_interface::digits;
  for (auto d : digits) {
    EXPECT_TRUE(mpa::core::IsDigit(d));
  }
}

TEST(MpaCoreUtils, IsDigit_InvalidIntInput)
{
  using int_interface::not_digits;
  for (auto d : not_digits) {
    EXPECT_FALSE(mpa::core::IsDigit(d));
  }
}

TEST(MpaCoreUtils, ToChar_ValidInput)
{
  using char_interface::digits;
  using char_interface::digits_size;
  for (int i = 0; i < digits_size; ++i) {
    EXPECT_EQ(digits[i], mpa::core::ToChar(i));
  }
}

TEST(MpaCoreUtils, ToChar_InvalidInput)
{
  using int_interface::not_digits;
  using int_interface::not_digits_size;
  for (int i = 0; i < not_digits_size; ++i) {
    // static cast needed for safe use of isdigit
    // https://en.cppreference.com/w/cpp/string/byte/isdigit
    EXPECT_FALSE(
        isdigit(static_cast<unsigned char>(mpa::core::ToChar(not_digits[i]))));
  }
}

TEST(MpaCoreUtils, ToDec_ValidInput)
{
  using char_interface::digits;
  using char_interface::digits_size;
  for (int i = 0; i < digits_size; ++i) {
    EXPECT_EQ(i, mpa::core::ToDec(digits[i]));
  }
}

TEST(MpaCoreUtils, ToDec_InvalidInput)
{
  using char_interface::not_digits;
  using char_interface::not_digits_size;
  for (int i = 0; i < not_digits_size; ++i) {
    const int not_digit = mpa::core::ToDec(not_digits[i]);
    EXPECT_FALSE(not_digit >= 0 && not_digit <= 9);
  }
}

TEST(MpaCoreUtils, IsAbsGreater_DiffSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"12345"};
  EXPECT_TRUE(mpa::core::IsAbsGreater(greater, smaller));
  EXPECT_FALSE(mpa::core::IsAbsGreater(smaller, greater));
}

TEST(MpaCoreUtils, IsAbsGreater_EqSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"1235"};
  EXPECT_TRUE(mpa::core::IsAbsGreater(greater, smaller));
  EXPECT_FALSE(mpa::core::IsAbsGreater(smaller, greater));
}

TEST(MpaCoreUtils, IsAbsGreater_EqSizeEqValue)
{
  const std::string smaller{"1234"};
  const std::string greater{"1234"};
  EXPECT_FALSE(mpa::core::IsAbsGreater(greater, smaller));
  EXPECT_FALSE(mpa::core::IsAbsGreater(smaller, greater));
}

TEST(MpaCoreUtils, IsAbsLess_DiffSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"12345"};
  EXPECT_TRUE(mpa::core::IsAbsLess(smaller, greater));
  EXPECT_FALSE(mpa::core::IsAbsLess(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsLess_EqSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"1235"};
  EXPECT_TRUE(mpa::core::IsAbsLess(smaller, greater));
  EXPECT_FALSE(mpa::core::IsAbsLess(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsLess_EqSizeEqValue)
{
  const std::string smaller{"1234"};
  const std::string greater{"1234"};
  EXPECT_FALSE(mpa::core::IsAbsLess(smaller, greater));
  EXPECT_FALSE(mpa::core::IsAbsLess(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsGreaterOrEqual_DiffSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"12345"};
  EXPECT_TRUE(mpa::core::IsAbsGreaterOrEqual(greater, smaller));
  EXPECT_FALSE(mpa::core::IsAbsGreaterOrEqual(smaller, greater));
}

TEST(MpaCoreUtils, IsAbsGreaterOrEqual_EqSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"1235"};
  EXPECT_TRUE(mpa::core::IsAbsGreaterOrEqual(greater, smaller));
  EXPECT_FALSE(mpa::core::IsAbsGreaterOrEqual(smaller, greater));
}

TEST(MpaCoreUtils, IsAbsGreaterOrEqual_EqSizeEqValue)
{
  const std::string smaller{"1234"};
  const std::string greater{"1234"};
  EXPECT_TRUE(mpa::core::IsAbsGreaterOrEqual(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsLessOrEqual_DiffSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"12345"};
  EXPECT_TRUE(mpa::core::IsAbsLessOrEqual(smaller, greater));
  EXPECT_FALSE(mpa::core::IsAbsLessOrEqual(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsLessOrEqual_EqSize)
{
  const std::string smaller{"1234"};
  const std::string greater{"1235"};
  EXPECT_TRUE(mpa::core::IsAbsLessOrEqual(smaller, greater));
  EXPECT_FALSE(mpa::core::IsAbsLessOrEqual(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsLessOrEqual_EqSizeEqValue)
{
  const std::string smaller{"1234"};
  const std::string greater{"1234"};
  EXPECT_TRUE(mpa::core::IsAbsLessOrEqual(greater, smaller));
}

TEST(MpaCoreUtils, IsAbsEqual_DiffSize)
{
  const std::string first{"12345"};
  const std::string second{"1234"};
  EXPECT_FALSE(mpa::core::IsAbsEqual(first, second));
}

TEST(MpaCoreUtils, IsAbsEqual_EqSize)
{
  const std::string first{"1235"};
  const std::string second{"1234"};
  EXPECT_FALSE(mpa::core::IsAbsEqual(first, second));
}

TEST(MpaCoreUtils, IsAbsEqual_EqSizeEqValue)
{
  const std::string first{"1234"};
  const std::string second{"1234"};
  EXPECT_TRUE(mpa::core::IsAbsEqual(first, second));
}

TEST(MpaCoreUtils, HasNonDigitSymbol_BelowSmallerLimit)
{
  const std::string num{"123/4"};
  EXPECT_TRUE(mpa::core::HasNonDigitSymbol(num));
}

TEST(MpaCoreUtils, HasNonDigitSymbol_AboveHigherLimit)
{
  const std::string num{"123:4"};
  EXPECT_TRUE(mpa::core::HasNonDigitSymbol(num));
}

TEST(MpaCoreUtils, HasNonDigitSymbol_InRange)
{
  const std::string num{"1234567890"};
  EXPECT_FALSE(mpa::core::HasNonDigitSymbol(num));
}

TEST(MpaCoreUtils, IsNegative_Empty)
{
  const std::string num;
  EXPECT_FALSE(mpa::core::IsNegative(num));
}

TEST(MpaCoreUtils, IsNegative_False)
{
  const std::string num1{"+"};
  const std::string num2{"_"};
  EXPECT_FALSE(mpa::core::IsNegative(num1));
  EXPECT_FALSE(mpa::core::IsNegative(num2));
}

TEST(MpaCoreUtils, IsNegative_True)
{
  const std::string num1{"-12345"};
  // IsNegative does not check the non-digit symbols
  const std::string num2{"-abc/^&"};
  EXPECT_TRUE(mpa::core::IsNegative(num1));
  EXPECT_TRUE(mpa::core::IsNegative(num2));
}

TEST(MpaCoreUtils, IsPositive_Empty)
{
  const std::string num;
  EXPECT_FALSE(mpa::core::IsPositive(num));
}

TEST(MpaCoreUtils, IsPositive_False)
{
  const std::string num1{"-"};
  const std::string num2{"_"};
  EXPECT_FALSE(mpa::core::IsPositive(num1));
  EXPECT_FALSE(mpa::core::IsPositive(num2));
}

TEST(MpaCoreUtils, IsPositive_True)
{
  const std::string num1{"+12345"};
  // Positive is either with plus sign at front or
  // starts with digit
  const std::string num2{"12345"};
  EXPECT_TRUE(mpa::core::IsPositive(num1));
  EXPECT_TRUE(mpa::core::IsPositive(num2));
}

TEST(MpaCoreUtils, HasPlusSignAtFront_Empty)
{
  const std::string num;
  EXPECT_FALSE(mpa::core::HasPlusSignAtFront(num));
}

TEST(MpaCoreUtils, HasPlusSignAtFront_False)
{
  const std::string num{"123"};
  EXPECT_FALSE(mpa::core::HasPlusSignAtFront(num));
}

TEST(MpaCoreUtils, HasPlusSignAtFront_True)
{
  // It does not check non-digit chars
  const std::string num{"+123abc%$"};
  EXPECT_TRUE(mpa::core::HasPlusSignAtFront(num));
}

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "mpaexcept.h"
#include "mpainteger.h"

using mpa::Integer;

TEST(MpaInteger, CtrNoThrow)
{
  ASSERT_NO_THROW(Integer num{"1234567890"});
  ASSERT_NO_THROW(Integer num{"-1234567890"});
}

TEST(MpaInteger, CtrNotNumbers)
{
  ASSERT_THROW(Integer num{"--1234567890"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"-1a234567890"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"1234567890-"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"-12%@34567890"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"12345ABX67890"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"abcdefghi"}, mpa::error::InvalidNumber);
  ASSERT_THROW(Integer num{"1a234567890"}, mpa::error::InvalidNumber);
}

TEST(MpaInteger, EqualOp)
{
  Integer num1{"123456"};
  Integer num2{"-123456"};
  Integer num3{"7890"};
  Integer num4{"-7890"};
  EXPECT_EQ(num1, num1);
  EXPECT_EQ(num2, num2);
  // explicitly test "equal" operator (not the !=)
  EXPECT_FALSE(num1 == num2);
  EXPECT_FALSE(num1 == num3);
  EXPECT_FALSE(num3 == num4);
}

TEST(MpaInteger, NotEqualOp)
{
  Integer num1{"123456"};
  Integer num2{"-123456"};
  Integer num3{"7890"};
  Integer num4{"-7890"};
  EXPECT_NE(num1, num2);
  EXPECT_NE(num1, num3);
  EXPECT_NE(num3, num4);

  // explicitly test "not equal" operator
  EXPECT_FALSE(num1 != num1);
  EXPECT_FALSE(num2 != num2);
}

TEST(MpaInteger, UnaryMinus)
{
  Integer positive{"123456"};
  Integer negative{"-123456"};
  EXPECT_EQ(negative, -positive);
  EXPECT_EQ(-negative, positive);
  EXPECT_NE(negative, -negative);
  EXPECT_NE(positive, -positive);
}

TEST(MpaInteger, UnaryPlus)
{
  Integer positive{"123456"};
  Integer negative{"-123456"};
  EXPECT_NE(negative, +positive);
  EXPECT_NE(+negative, positive);
  EXPECT_EQ(negative, +negative);
  EXPECT_EQ(+positive, positive);
}

TEST(MpaInteger, GreaterThanOp)
{
  Integer num1{"1234"};
  Integer num2{"-123456"};
  Integer num3{"5678"};
  Integer num4{"-7890"};
  EXPECT_GT(num1, num2);
  EXPECT_GT(num3, num1);
  EXPECT_GT(num4, num2);

  EXPECT_FALSE(num1 > num1);
  EXPECT_FALSE(num2 > num2);
}

TEST(MpaInteger, LessThanOp)
{
  Integer num1{"1234"};
  Integer num2{"-123456"};
  Integer num3{"5678"};
  Integer num4{"-7890"};
  EXPECT_LT(num2, num1);
  EXPECT_LT(num1, num3);
  EXPECT_LT(num2, num4);

  EXPECT_FALSE(num1 < num1);
  EXPECT_FALSE(num2 < num2);
}

TEST(MpaInteger, GreaterOrEqOp)
{
  Integer num1{"1234"};
  Integer num2{"-123456"};
  Integer num3{"5678"};
  Integer num4{"-7890"};
  EXPECT_GE(num1, num2);
  EXPECT_GE(num3, num1);
  EXPECT_GE(num4, num2);
  EXPECT_GE(num1, num1);
  EXPECT_GE(num2, num2);
}

TEST(MpaInteger, LessOrEqOp)
{
  Integer num1{"1234"};
  Integer num2{"-123456"};
  Integer num3{"5678"};
  Integer num4{"-7890"};
  EXPECT_LE(num2, num1);
  EXPECT_LE(num1, num3);
  EXPECT_LE(num2, num4);
  EXPECT_LE(num1, num1);
  EXPECT_LE(num2, num2);
}

TEST(MpaInteger, PutIntoStreamOpPositive)
{
  Integer num{"123"};
  std::ostringstream oss;
  oss << num;
  EXPECT_EQ("123", oss.str());
}

TEST(MpaInteger, PutIntoStreamOpNegative)
{
  Integer num{"-123"};
  std::ostringstream oss;
  oss << num;
  EXPECT_EQ("-123", oss.str());
}

TEST(MpaInteger, PrefixIncrementOpPositive)
{
  // ++12
  Integer num{"12"};
  const Integer expected{"13"};
  const auto actual = ++num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PrefixIncrementOpNegative)
{
  // ++(-12)
  Integer num{"-12"};
  const Integer expected{"-11"};
  const auto actual = ++num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PrefixIncrementOpNegativeToPositive)
{
  // ++(-1)
  Integer num{"-1"};
  const Integer expected{"0"};
  const auto actual = ++num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PrefixDecrementOpPositive)
{
  // --12
  Integer num{"12"};
  const Integer expected{"11"};
  const auto actual = --num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PrefixDecrementOpNegative)
{
  // --(-12)
  Integer num{"-12"};
  const Integer expected{"-13"};
  const auto actual = --num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PrefixDecrementOpPositiveToNegative)
{
  // --0
  Integer num{"0"};
  const Integer expected{"-1"};
  const auto actual = --num;
  EXPECT_EQ(actual, expected);
}

TEST(MpaInteger, PostfixIncrementOpPositive)
{
  // 12++
  Integer num{"12"};
  const auto old = num;
  const Integer expected{"13"};

  const auto actual = num++;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, PostfixIncrementOpNegative)
{
  // (-12)++
  Integer num{"-12"};
  const auto old = num;
  const Integer expected{"-11"};

  const auto actual = num++;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, PostfixIncrementOpNegativeToPositive)
{
  // (-1)++
  Integer num{"-1"};
  const auto old = num;
  const Integer expected{"0"};

  const auto actual = num++;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, PostfixDecrementOpPositive)
{
  // 12--
  Integer num{"12"};
  const auto old = num;
  const Integer expected{"11"};

  const auto actual = num--;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, PostfixDecrementOpNegative)
{
  // (-12)--
  Integer num{"-12"};
  const auto old = num;
  const Integer expected{"-13"};

  const auto actual = num--;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, PostfixDecrementOpPositiveToNegative)
{
  // 0--
  Integer num{"0"};
  const auto old = num;
  const Integer expected{"-1"};

  const auto actual = num--;
  EXPECT_EQ(actual, old);
  EXPECT_EQ(num, expected);
}

TEST(MpaInteger, AddIntegersSameSignPositive)
{
  // 1234567890 + 1234567890
  Integer lhs{"1234567890"};
  Integer rhs{"1234567890"};
  Integer res{"2469135780"};
  EXPECT_EQ(res, lhs + rhs);
}

TEST(MpaInteger, AddIntegersSameSignNegative)
{
  // -1234567890 + (-1234567890)
  Integer lhs{"-1234567890"};
  Integer rhs{"-1234567890"};
  Integer res{"-2469135780"};
  EXPECT_EQ(res, lhs + rhs);
}

TEST(MpaInteger, AddZero)
{
  // -1234567890 + 0
  Integer lhs{"-1234567890"};
  Integer rhs{"0"};
  EXPECT_EQ(lhs, lhs + rhs);
}

TEST(MpaInteger, AddZeroes)
{
  // -1234567890 + 0
  Integer lhs{"0"};
  Integer rhs{"0"};
  EXPECT_EQ(lhs, lhs + rhs);
}

TEST(MpaInteger, Additivity)
{
  // 150 + 50 = 50 + 150
  Integer lhs{"150"};
  Integer rhs{"50"};
  EXPECT_EQ(lhs + rhs, rhs + lhs);
}

TEST(MpaInteger, AddIntegersDiffSignLhsIsNegative)
{
  // -200 + 150
  Integer lhs{"-200"};
  Integer rhs{"150"};
  Integer res{"-50"};
  EXPECT_EQ(res, lhs + rhs);
}

TEST(MpaInteger, AddIntegersDiffSignRhsIsNegative)
{
  // 200 + (-150)
  Integer lhs{"200"};
  Integer rhs{"-150"};
  Integer res{"50"};
  EXPECT_EQ(res, lhs + rhs);
}

TEST(MpaInteger, SubtractIntegersSameSignPositive)
{
  // 200 - 150
  Integer lhs{"200"};
  Integer rhs{"150"};
  Integer res{"50"};
  EXPECT_EQ(res, lhs - rhs);
}

TEST(MpaInteger, SubtractIntegersSameSignNegative)
{
  // -200 - (-150)
  Integer lhs{"-200"};
  Integer rhs{"-150"};
  Integer res{"-50"};
  EXPECT_EQ(res, lhs - rhs);
}

TEST(MpaInteger, SubtractIntegersDiffSignLhsIsNegative)
{
  // -200 - 150
  Integer lhs{"-200"};
  Integer rhs{"150"};
  Integer res{"-350"};
  EXPECT_EQ(res, lhs - rhs);
}

TEST(MpaInteger, SubtractIntegersDiffSignRhsIsNegative)
{
  // 200 - (-150)
  Integer lhs{"200"};
  Integer rhs{"-150"};
  Integer res{"350"};
  EXPECT_EQ(res, lhs - rhs);
}

TEST(MpaInteger, SubtractZero)
{
  // 200 - 0
  Integer lhs{"200"};
  Integer rhs{"0"};
  EXPECT_EQ(lhs, lhs - rhs);
}

TEST(MpaInteger, SubtractFromZero)
{
  // 0 - 150
  Integer lhs{"0"};
  Integer rhs{"150"};
  Integer res{"-150"};
  EXPECT_EQ(res, lhs - rhs);
}

TEST(MpaInteger, SubtractZeroes)
{
  // 0 - 0
  Integer lhs{"0"};
  Integer rhs{"0"};
  EXPECT_EQ(lhs, lhs - rhs);
}

TEST(MpaInteger, MultiplyIntegersSameSignPositive)
{
  // 12 * 12
  Integer lhs{"12"};
  Integer rhs{"12"};
  Integer res{"144"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersSameSignNegative)
{
  // -12 * (-12)
  Integer lhs{"-12"};
  Integer rhs{"-12"};
  Integer res{"144"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersDiffSignLhsIsNegative)
{
  // -12 * 12
  Integer lhs{"-12"};
  Integer rhs{"12"};
  Integer res{"-144"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersDiffSignRhsIsNegative)
{
  // 12 * -12
  Integer lhs{"12"};
  Integer rhs{"-12"};
  Integer res{"-144"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersLhsIsZero)
{
  // 0 * 12
  Integer lhs{"0"};
  Integer rhs{"12"};
  Integer res{"0"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersRhsIsZero)
{
  // 12 * 0
  Integer lhs{"12"};
  Integer rhs{"0"};
  Integer res{"0"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersZeroes)
{
  // 0 * 0
  Integer lhs{"0"};
  Integer rhs{"0"};
  Integer res{"0"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersLhsIsOne)
{
  // 1 * 12
  Integer lhs{"1"};
  Integer rhs{"12"};
  Integer res{"12"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, MultiplyIntegersRhsIsOne)
{
  // 12 * 1
  Integer lhs{"12"};
  Integer rhs{"1"};
  Integer res{"12"};
  EXPECT_EQ(res, lhs * rhs);
}

TEST(MpaInteger, Commutativity)
{
  // 12 * 13 = 13 * 12
  Integer lhs{"12"};
  Integer rhs{"13"};
  EXPECT_EQ(lhs * rhs, rhs * lhs);
}

TEST(MpaInteger, DivideIntegersSameSignPositive)
{
  // 144 / 12
  Integer lhs{"144"};
  Integer rhs{"12"};
  Integer res{"12"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, DivideIntegersSameSignNegative)
{
  // -144 / (-12)
  Integer lhs{"-144"};
  Integer rhs{"-12"};
  Integer res{"12"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, DivideIntegersDiffSignLhsIsNegative)
{
  // -144 / 12
  Integer lhs{"-144"};
  Integer rhs{"12"};
  Integer res{"-12"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, DivideIntegersDiffSignRhsIsNegative)
{
  // 144 / (-12)
  Integer lhs{"144"};
  Integer rhs{"-12"};
  Integer res{"-12"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, DivideIntegersLhsIsZero)
{
  // 0 / 12
  Integer lhs{"0"};
  Integer rhs{"12"};
  Integer res{"0"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, DivideIntegersRhsIsZero)
{
  // 12 / 0
  Integer lhs{"144"};
  Integer rhs{"0"};
  EXPECT_THROW(lhs / rhs, mpa::error::DivisionByZero);
}

TEST(MpaInteger, DivideIntegersZeroes)
{
  // 0 / 0
  Integer lhs{"0"};
  Integer rhs{"0"};
  EXPECT_THROW(lhs / rhs, mpa::error::DivisionByZero);
}

TEST(MpaInteger, IntegerDivision)
{
  // 26 / 20
  Integer lhs{"26"};
  Integer rhs{"20"};
  Integer res{"1"};
  EXPECT_EQ(res, lhs / rhs);
}

TEST(MpaInteger, GetReminderSameSignPositive)
{
  // 26 % 20
  Integer lhs{"26"};
  Integer rhs{"20"};
  Integer res{"6"};
  EXPECT_EQ(res, lhs % rhs);
}

TEST(MpaInteger, GetReminderSameSignNegative)
{
  // -26 % (-20)
  Integer lhs{"-26"};
  Integer rhs{"-20"};
  Integer res{"6"};
  EXPECT_EQ(res, lhs % rhs);
}

TEST(MpaInteger, GetReminderDiffSignLhsIsNegative)
{
  // -26 % 20
  Integer lhs{"-26"};
  Integer rhs{"20"};
  Integer res{"-6"};
  EXPECT_EQ(res, lhs % rhs);
}

TEST(MpaInteger, GetReminderDiffSignRhsIsNegative)
{
  // 26 % (-20)
  Integer lhs{"26"};
  Integer rhs{"-20"};
  Integer res{"-6"};
  EXPECT_EQ(res, lhs % rhs);
}

TEST(MpaInteger, GetReminderLhsIsZero)
{
  // 0 % 20
  Integer lhs{"0"};
  Integer rhs{"20"};
  Integer res{"0"};
  EXPECT_EQ(res, lhs % rhs);
}

TEST(MpaInteger, GetReminderRhsIsZero)
{
  // 26 % 0
  Integer lhs{"26"};
  Integer rhs{"0"};
  EXPECT_THROW(lhs % rhs, mpa::error::DivisionByZero);
}

TEST(MpaInteger, GetReminderZeroes)
{
  // 0 % 0
  Integer lhs{"0"};
  Integer rhs{"0"};
  EXPECT_THROW(lhs % rhs, mpa::error::DivisionByZero);
}

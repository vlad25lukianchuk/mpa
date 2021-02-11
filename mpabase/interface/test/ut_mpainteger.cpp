#include <gtest/gtest.h>

#include <sstream>

#include "mpainteger.h"

using mpa::Integer;

TEST(MpaInteger, CtrNoThrow)
{
  ASSERT_NO_THROW(Integer num{"1234567890"});
  ASSERT_NO_THROW(Integer num{"-1234567890"});
}

TEST(MpaInteger, CtrNotNumbers)
{
  ASSERT_THROW(Integer num{"--1234567890"}, std::runtime_error);
  ASSERT_THROW(Integer num{"-1a234567890"}, std::runtime_error);
  ASSERT_THROW(Integer num{"1234567890-"}, std::runtime_error);
  ASSERT_THROW(Integer num{"-12%@34567890"}, std::runtime_error);
  ASSERT_THROW(Integer num{"12345ABX67890"}, std::runtime_error);
  ASSERT_THROW(Integer num{"abcdefghi"}, std::runtime_error);
  ASSERT_THROW(Integer num{"1a234567890"}, std::runtime_error);
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

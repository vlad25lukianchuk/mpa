#include <gtest/gtest.h>

#include <string>

#include "mpamath.h"
#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Multiply;
using mpa::math::impl::MultiplyImpl;

TEST(MpaMultiplyImpl, DiffSizes)
{
  const std::string lhs{"199"};
  const std::string rhs{"12"};
  EXPECT_EQ("2388", MultiplyImpl(lhs, rhs));
}

TEST(MpaMultiplyImpl, SameSizes)
{
  const std::string lhs{"12"};
  const std::string rhs{"12"};
  EXPECT_EQ("144", MultiplyImpl(lhs, rhs));
}

// TODO: fix multiply by zero (a lot of trailing zeroes)
TEST(MpaMultiplyImpl, DISABLED_MultiplyByZero)
{
  const std::string lhs{"1234567890"};
  const std::string rhs{"0"};
  EXPECT_EQ("0", MultiplyImpl(lhs, rhs));
}

TEST(MpaMultiplyImpl, BothAreZeros)
{
  const std::string lhs{"0"};
  const std::string rhs{"0"};
  EXPECT_EQ("0", MultiplyImpl(lhs, rhs));
}

TEST(MpaMultiplyImpl, LargeNumbers)
{
  const std::string lhs{"1234567890123456789012345678901234567890"};
  const std::string rhs{"1000000000000000000000000000000000000000"};
  const std::string res{
      "1234567890123456789012345678901234567890"
      "000000000000000000000000000000000000000"};
  EXPECT_EQ(res, MultiplyImpl(lhs, rhs));
}

TEST(MpaMultiplyImpl, LargeDigits)
{
  const std::string lhs{"999"};
  const std::string rhs{"888"};
  EXPECT_EQ("887112", MultiplyImpl(lhs, rhs));
}

TEST(MpaMultiply, BothPositiveLhsIsLarger)
{
  // 999 * 12
  const Number lhs{"999", Sign::kPlus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"11988", Sign::kPlus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, BothPositiveRhsIsLarger)
{
  // 12 * 999
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"999", Sign::kPlus};
  EXPECT_EQ((Number{"11988", Sign::kPlus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, BothNegativeAbsLhsIsLarger)
{
  // (-999) * -12
  const Number lhs{"999", Sign::kMinus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"11988", Sign::kPlus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, BothNegativeAbsRhsIsLarger)
{
  // -12 * (-999)
  const Number lhs{"12", Sign::kMinus};
  const Number rhs{"999", Sign::kMinus};
  EXPECT_EQ((Number{"11988", Sign::kPlus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, DiffSignLhsIsNegativeAbsLhsIsGreater)
{
  // -999 * 12
  const Number lhs{"999", Sign::kMinus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"11988", Sign::kMinus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, DiffSignLhsIsNegativeAbsRhsIsGreater)
{
  // -12 * 999
  const Number lhs{"12", Sign::kMinus};
  const Number rhs{"999", Sign::kPlus};
  EXPECT_EQ((Number{"11988", Sign::kMinus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, DiffSignRhsIsNegativeAbsLhsIsGreater)
{
  // 999 * (-12)
  const Number lhs{"999", Sign::kPlus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"11988", Sign::kMinus}), Multiply(lhs, rhs));
}

TEST(MpaMultiply, DiffSignRhsIsNegativeAbsRhsIsGreater)
{
  // 12 * (-999)
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"999", Sign::kMinus};
  EXPECT_EQ((Number{"11988", Sign::kMinus}), Multiply(lhs, rhs));
}

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "mpamath.h"
#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Divide;
using mpa::math::impl::DivideImpl;

TEST(MpaDivideImpl, SameSize)
{
  const std::string lhs{"49"};
  const std::string rhs{"12"};
  EXPECT_EQ("4", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, DiffSize)
{
  const std::string lhs{"144"};
  const std::string rhs{"12"};
  EXPECT_EQ("12", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, OneZeroAtTheEnd)
{
  const std::string lhs{"124"};
  const std::string rhs{"12"};
  EXPECT_EQ("10", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, ZeroesAtTheEnd)
{
  const std::string lhs{"1211"};
  const std::string rhs{"12"};
  EXPECT_EQ("100", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, SameValues)
{
  const std::string lhs{"1211"};
  const std::string rhs{"1211"};
  EXPECT_EQ("1", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, LargeNumbers)
{
  const std::string lhs{"1234567890123456789012345678901234567890"};
  const std::string rhs{"1000000000000000000000000000000000000000"};
  EXPECT_EQ("1", DivideImpl(lhs, rhs));
}

TEST(MpaDivideImpl, NumbersWithZeroes)
{
  const std::string lhs{"1000000"};
  const std::string rhs{"100"};
  EXPECT_EQ("10000", DivideImpl(lhs, rhs));
}

TEST(MpaDivide, RhsIsZero)
{
  // 12 / 0
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"0"};
  EXPECT_THROW(Divide(lhs, rhs), std::runtime_error);
}

TEST(MpaDivide, LhsIsZero)
{
  // 0 / 12
  const Number lhs{"0"};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ(Number{"0"}, Divide(lhs, rhs));
}

TEST(MpaDivide, LhsIsAbsLessThanRhs)
{
  // 10 / 12
  const Number lhs{"10", Sign::kPlus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ(Number{"0"}, Divide(lhs, rhs));
}

TEST(MpaDivide, SameSignPositive)
{
  // 144 / 12
  const Number lhs{"144", Sign::kPlus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"12", Sign::kPlus}), Divide(lhs, rhs));
}

TEST(MpaDivide, SameSignNegative)
{
  // - 144 / (-12)
  const Number lhs{"144", Sign::kMinus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"12", Sign::kPlus}), Divide(lhs, rhs));
}

TEST(MpaDivide, DiffSignLhsNegative)
{
  // -144 / 12
  const Number lhs{"144", Sign::kMinus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"12", Sign::kMinus}), Divide(lhs, rhs));
}

TEST(MpaDivide, DiffSignRhsNegative)
{
  // 144 / (-12)
  const Number lhs{"144", Sign::kPlus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"12", Sign::kMinus}), Divide(lhs, rhs));
}

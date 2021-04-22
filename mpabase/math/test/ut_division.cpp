#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "mpaexcept.h"
#include "mpamath.h"
#include "mpanumber.h"
//#include "mpastandardalgorithmsimpl.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Divide;
// using mpa::math::impl::StandardAlgorithmsImpl;

// class MpaDivideImplTest : public ::testing::Test {
// protected:
//  StandardAlgorithmsImpl impl_;
//};

// TEST_F(MpaDivideImplTest, SameSize)
//{
//  const std::string lhs{"49"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("4", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, DiffSize)
//{
//  const std::string lhs{"144"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("12", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, OneZeroAtTheEnd)
//{
//  const std::string lhs{"124"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("10", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, ZeroesAtTheEnd)
//{
//  const std::string lhs{"1211"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("100", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, SameValues)
//{
//  const std::string lhs{"1211"};
//  const std::string rhs{"1211"};
//  EXPECT_EQ("1", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, LargeNumbers)
//{
//  const std::string lhs{"1234567890123456789012345678901234567890"};
//  const std::string rhs{"1000000000000000000000000000000000000000"};
//  EXPECT_EQ("1", impl_.Divide(lhs, rhs));
//}

// TEST_F(MpaDivideImplTest, NumbersWithZeroes)
//{
//  const std::string lhs{"1000000"};
//  const std::string rhs{"100"};
//  EXPECT_EQ("10000", impl_.Divide(lhs, rhs));
//}

TEST(MpaDivide, RhsIsZero)
{
  // 12 / 0
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"0"};
  EXPECT_THROW(Divide(lhs, rhs), mpa::error::DivisionByZero);
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

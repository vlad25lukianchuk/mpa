#include <gtest/gtest.h>

#include <string>

#include "mpamath.h"
#include "mpanumber.h"
//#include "mpastandardalgorithmsimpl.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Multiply;
// using mpa::math::impl::StandardAlgorithmsImpl;

// class MpaMultiplyImplTest : public ::testing::Test {
// protected:
//  StandardAlgorithmsImpl impl_;
//};

// TEST_F(MpaMultiplyImplTest, DiffSizes)
//{
//  const std::string lhs{"199"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("2388", impl_.Multiply(lhs, rhs));
//}

// TEST_F(MpaMultiplyImplTest, SameSizes)
//{
//  const std::string lhs{"12"};
//  const std::string rhs{"12"};
//  EXPECT_EQ("144", impl_.Multiply(lhs, rhs));
//}

// TEST_F(MpaMultiplyImplTest, LargeNumbers)
//{
//  const std::string lhs{"1234567890123456789012345678901234567890"};
//  const std::string rhs{"1000000000000000000000000000000000000000"};
//  const std::string res{
//      "1234567890123456789012345678901234567890"
//      "000000000000000000000000000000000000000"};
//  EXPECT_EQ(res, impl_.Multiply(lhs, rhs));
//}

// TEST_F(MpaMultiplyImplTest, LargeDigits)
//{
//  const std::string lhs{"999"};
//  const std::string rhs{"888"};
//  EXPECT_EQ("887112", impl_.Multiply(lhs, rhs));
//}

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

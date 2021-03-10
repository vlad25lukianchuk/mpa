#include <gtest/gtest.h>

#include "mpamath.h"
#include "mpamathimpl.h"
#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Subtract;
using mpa::math::impl::SubtractImpl;

TEST(MpaSubtractImpl, DiffSizes)
{
  const std::string larger{"1234"};
  const std::string smaller{"12"};
  EXPECT_EQ("1222", SubtractImpl(larger, smaller));
}

TEST(MpaSubtractImpl, SameSizeDiffValues)
{
  const std::string larger{"1234"};
  const std::string smaller{"1233"};
  EXPECT_EQ("1", SubtractImpl(larger, smaller));
}

TEST(MpaSubtractImpl, SameSizeSameValues)
{
  const std::string larger{"1234"};
  const std::string smaller{"1234"};
  EXPECT_EQ("0", SubtractImpl(larger, smaller));
}

TEST(MpaSubtractImpl, LargeNumbers)
{
  const std::string larger{"2000000000000000000000000000000000000000000000"};
  const std::string smaller{"1000000000000000000000000000000000000000000000"};
  EXPECT_EQ(smaller, SubtractImpl(larger, smaller));
}

TEST(MpaSubtractImpl, SubtractZero)
{
  const std::string larger{"20"};
  const std::string smaller{"0"};
  EXPECT_EQ(larger, SubtractImpl(larger, smaller));
}

TEST(MpaSubtractImpl, SubtractDiffSizesSubtractorDigitsAreSmaller)
{
  const std::string larger{"1000"};
  const std::string smaller{"999"};
  EXPECT_EQ("1", SubtractImpl(larger, smaller));
}

TEST(MpaSubtract, EgSignPositiveLhsIsGreater)
{
  // 1234 - 123
  const Number lhs{"1234", Sign::kPlus};
  const Number rhs{"123", Sign::kPlus};
  EXPECT_EQ((Number{"1111", Sign::kPlus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, EgSignPositiveRhsIsGreater)
{
  // 123 - 1234
  const Number lhs{"123", Sign::kPlus};
  const Number rhs{"1234", Sign::kPlus};
  EXPECT_EQ((Number{"1111", Sign::kMinus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, EgSignNegativeLhsIsGreater)
{
  // - 1234 - (-123)
  const Number lhs{"1234", Sign::kMinus};
  const Number rhs{"123", Sign::kMinus};
  EXPECT_EQ((Number{"1111", Sign::kMinus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, EgSignNegativeRhsIsGreater)
{
  // - 123 - (-1234)
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"1234", Sign::kMinus};
  EXPECT_EQ((Number{"1111", Sign::kPlus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, DiffSignLhsIsNegativeLhsIsGreater)
{
  // - 1234 - 123
  const Number lhs{"1234", Sign::kMinus};
  const Number rhs{"123", Sign::kPlus};
  EXPECT_EQ((Number{"1357", Sign::kMinus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, DiffSignLhsIsNegativeRhsIsGreater)
{
  // - 123 - 1234
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"1234", Sign::kPlus};
  EXPECT_EQ((Number{"1357", Sign::kMinus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, DiffSignRhsIsNegativeLhsIsGreater)
{
  // 1234 - (-123)
  const Number lhs{"1234", Sign::kPlus};
  const Number rhs{"123", Sign::kMinus};
  EXPECT_EQ((Number{"1357", Sign::kPlus}), Subtract(lhs, rhs));
}

TEST(MpaSubtract, DiffSignRhsIsNegativeRhsIsGreater)
{
  // 123 - (-1234)
  const Number lhs{"123", Sign::kPlus};
  const Number rhs{"1234", Sign::kMinus};
  EXPECT_EQ((Number{"1357", Sign::kPlus}), Subtract(lhs, rhs));
}

#include <gtest/gtest.h>

#include "mpamath.h"
#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Add;
using mpa::math::impl::AddImpl;

TEST(MpaAddImpl, DiffSizes)
{
  const std::string larger{"123"};
  const std::string smaller{"12"};
  EXPECT_EQ("135", AddImpl(larger, smaller));
}

TEST(MpaAddImpl, SameSize)
{
  const std::string larger{"123"};
  const std::string smaller{"123"};
  EXPECT_EQ("246", AddImpl(larger, smaller));
}

TEST(MpaAddImpl, LargeNumbers)
{
  const std::string larger{"10000000000000000000000000000000000"};
  const std::string smaller{"10000000000000000000000000000000000"};
  EXPECT_EQ("20000000000000000000000000000000000", AddImpl(larger, smaller));
}

TEST(MpaAddImpl, AddZero)
{
  const std::string larger{"1234567890"};
  const std::string smaller{"0"};
  EXPECT_EQ(larger, AddImpl(larger, smaller));
}

TEST(MpaAddImpl, AddZeroes)
{
  const std::string larger{"0"};
  const std::string smaller{"0"};
  EXPECT_EQ(larger, AddImpl(larger, smaller));
}

TEST(MpaAddImpl, SameSizeResSizeIncreased)
{
  const std::string larger{"999"};
  const std::string smaller{"999"};
  EXPECT_EQ("1998", AddImpl(larger, smaller));
}

TEST(MpaAddImpl, DiffSizeResSizeIncreased)
{
  const std::string larger{"9999"};
  const std::string smaller{"999"};
  EXPECT_EQ("10998", AddImpl(larger, smaller));
}

TEST(MpaAdd, EqSignEqValuePositive)
{
  // 123 + 123
  const Number lhs{"123"};
  const Number rhs{"123"};
  EXPECT_EQ(Number{"246"}, Add(lhs, rhs));
}

TEST(MpaAdd, EqSignLhsGreaterPositive)
{
  Number lhs{"124"};
  const Number rhs{"123"};
  // eq size: 124 + 123
  EXPECT_EQ(Number{"247"}, Add(lhs, rhs));

  // diff size: 123456 + 123
  lhs = Number{"123456"};
  EXPECT_EQ(Number{"123579"}, Add(lhs, rhs));
}

TEST(MpaAdd, EqSignRhsGreaterPositive)
{
  const Number lhs{"123"};
  Number rhs{"124"};
  // 123 + 124
  EXPECT_EQ(Number{"247"}, Add(lhs, rhs));

  // 123 + 123456
  rhs = Number{"123456"};
  EXPECT_EQ(Number{"123579"}, Add(lhs, rhs));
}

TEST(MpaAdd, EqSignEqValueNegative)
{
  // -123 - 123
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"123", Sign::kMinus};
  EXPECT_EQ((Number{"246", Sign::kMinus}), Add(lhs, rhs));
}

TEST(MpaAdd, EqSignLhsGreaterNegative)
{
  // eq size: -123 - 124
  const Number lhs{"123", Sign::kMinus};
  Number rhs{"124", Sign::kMinus};
  EXPECT_EQ((Number{"247", Sign::kMinus}), Add(lhs, rhs));

  // diff size: -123 -123456
  rhs = Number{"123456", Sign::kMinus};
  EXPECT_EQ((Number{"123579", Sign::kMinus}), Add(lhs, rhs));
}

TEST(MpaAdd, EqSignRhsGreaterNegative)
{
  // eq size -124 - 123
  Number lhs{"124", Sign::kMinus};
  const Number rhs{"123", Sign::kMinus};
  EXPECT_EQ((Number{"247", Sign::kMinus}), Add(lhs, rhs));

  // diff size -123456 - 124
  lhs = Number{"123456", Sign::kMinus};
  EXPECT_EQ((Number{"123579", Sign::kMinus}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignLhsNegativeLhsValueGreater)
{
  // -123 + 120
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"120", Sign::kPlus};
  EXPECT_EQ((Number{"3", Sign::kMinus}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignLhsNegativeLhsValueSmaller)
{
  // -123 + 125
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"125", Sign::kPlus};
  EXPECT_EQ((Number{"2", Sign::kPlus}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignLhsNegativeEqValues)
{
  // -123 + 123
  const Number lhs{"123", Sign::kMinus};
  const Number rhs{"123", Sign::kPlus};
  EXPECT_EQ((Number{"0"}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignRhsNegativeRhsValueGreater)
{
  // 123 + (-125)
  const Number lhs{"123", Sign::kPlus};
  const Number rhs{"125", Sign::kMinus};
  EXPECT_EQ((Number{"2", Sign::kMinus}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignRhsNegativeRhsValueSmaller)
{
  // 123 + (-120)
  const Number lhs{"123", Sign::kPlus};
  const Number rhs{"120", Sign::kMinus};
  EXPECT_EQ((Number{"3", Sign::kPlus}), Add(lhs, rhs));
}

TEST(MpaAdd, DiffSignRhsNegativeEqValues)
{
  // 123 + (-123)
  const Number lhs{"123", Sign::kPlus};
  const Number rhs{"123", Sign::kMinus};
  EXPECT_EQ((Number{"0"}), Add(lhs, rhs));
}

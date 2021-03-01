#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "mpaexcept.h"
#include "mpamath.h"
#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;
using mpa::math::Reminder;
using mpa::math::impl::ReminderImpl;

TEST(MpaReminderImpl, SameSize)
{
  const std::string lhs{"49"};
  const std::string rhs{"12"};
  EXPECT_EQ("1", ReminderImpl(lhs, rhs));
}

TEST(MpaReminderImpl, DiffSize)
{
  const std::string lhs{"145"};
  const std::string rhs{"12"};
  EXPECT_EQ("1", ReminderImpl(lhs, rhs));
}

TEST(MpaReminderImpl, MultipleDigitReminder)
{
  const std::string lhs{"1211"};
  const std::string rhs{"12"};
  EXPECT_EQ("11", ReminderImpl(lhs, rhs));
}

TEST(MpaReminderImpl, SameValues)
{
  const std::string lhs{"1211"};
  const std::string rhs{"1211"};
  EXPECT_EQ("0", ReminderImpl(lhs, rhs));
}

TEST(MpaReminderImpl, LargeNumbers)
{
  const std::string lhs{"1234567890123456789012345678901234567890"};
  const std::string rhs{"1000000000000000000000000000000000000000"};
  EXPECT_EQ("234567890123456789012345678901234567890", ReminderImpl(lhs, rhs));
}

TEST(MpaReminder, RhsIsZero)
{
  // 12 % 0
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"0"};
  EXPECT_THROW(Reminder(lhs, rhs), mpa::error::DivisionByZero);
}

TEST(MpaReminder, LhsIsZero)
{
  // 0 % 12
  const Number lhs{"0"};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"0"}), Reminder(lhs, rhs));
}

TEST(MpaReminder, LhsIsAbsLessThanRhs)
{
  // 12 % 14
  const Number lhs{"12", Sign::kPlus};
  const Number rhs{"14", Sign::kPlus};
  EXPECT_EQ((Number{"12", Sign::kPlus}), Reminder(lhs, rhs));
}

TEST(MpaReminder, SameSignPositive)
{
  // 150 % 12
  const Number lhs{"150", Sign::kPlus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"6", Sign::kPlus}), Reminder(lhs, rhs));
}

TEST(MpaReminder, SameSignNegative)
{
  // -150 % (-12)
  const Number lhs{"150", Sign::kMinus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"6", Sign::kPlus}), Reminder(lhs, rhs));
}

TEST(MpaReminder, DiffSignLhsNegative)
{
  // -150 % 12
  const Number lhs{"150", Sign::kMinus};
  const Number rhs{"12", Sign::kPlus};
  EXPECT_EQ((Number{"6", Sign::kMinus}), Reminder(lhs, rhs));
}

TEST(MpaReminder, DiffSignRhsNegative)
{
  // 150 % (-12)
  const Number lhs{"150", Sign::kPlus};
  const Number rhs{"12", Sign::kMinus};
  EXPECT_EQ((Number{"6", Sign::kMinus}), Reminder(lhs, rhs));
}

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

#include "mpanumber.h"

using mpa::core::Number;
using mpa::core::Sign;

TEST(MpaNumber, DefaultCtr)
{
  Number number;
  // Default number has empty value and is positive
  EXPECT_TRUE(number.value().empty());
  EXPECT_EQ(number.sign(), Sign::kPlus);
}

TEST(MpaNumber, NonDefaultCtr)
{
  const std::string value{"12345"};
  Number number1{value, Sign::kPlus};
  Number number2{value, Sign::kMinus};
  Number number3{value};
  EXPECT_EQ(number1.value(), value);
  EXPECT_EQ(number1.sign(), Sign::kPlus);

  EXPECT_EQ(number2.value(), value);
  EXPECT_EQ(number2.sign(), Sign::kMinus);

  EXPECT_EQ(number3.value(), value);
  EXPECT_EQ(number3.sign(), Sign::kPlus);
}

TEST(MpaNumber, UnaryMinusLValues)
{
  const Number positive{"123"};

  // change sign to minus
  auto tmp = -positive;
  EXPECT_EQ(tmp.value(), positive.value());
  EXPECT_EQ(tmp.sign(), Sign::kMinus);

  // change sign back to plus
  tmp = -tmp;
  EXPECT_EQ(tmp.value(), positive.value());
  EXPECT_EQ(tmp.sign(), Sign::kPlus);
}

TEST(MpaNumber, UnaryMinusRValues)
{
  const std::string val{"123"};

  auto tmp = -Number{val};
  EXPECT_EQ(tmp.value(), val);
  EXPECT_EQ(tmp.sign(), Sign::kMinus);

  tmp = -Number{val, Sign::kMinus};
  EXPECT_EQ(tmp.value(), val);
  EXPECT_EQ(tmp.sign(), Sign::kPlus);
}

TEST(MpaNumber, UnaryPlus)
{
  Number num{"123"};
  auto tmp = +num;
  EXPECT_EQ(tmp.value(), num.value());
  EXPECT_EQ(tmp.sign(), num.sign());

  // change sign to negative, nothing should be changed
  num = -num;
  tmp = +num;
  EXPECT_EQ(tmp.value(), num.value());
  EXPECT_EQ(tmp.sign(), num.sign());
}

TEST(MpaNumber, EqualOp)
{
  Number num1{"123"};
  Number num2{"123"};

  // equal
  EXPECT_TRUE(num1 == num2);

  // different signs
  EXPECT_FALSE(num1 == -num2);

  // equal signs, diff values
  Number num3{"124"};
  EXPECT_FALSE(num1 == num3);
}

TEST(MpaNumber, NotEqualOp)
{
  Number num1{"123"};
  Number num2{"123"};

  // equal
  EXPECT_FALSE(num1 != num2);

  // different signs
  EXPECT_TRUE(num1 != -num2);

  // equal signs, diff values
  Number num3{"124"};
  EXPECT_TRUE(num1 != num3);
}

TEST(MpaNumber, GreaterThanOp)
{
  Number num1{"123"};
  Number num2{"1234"};
  Number num3{"123", Sign::kMinus};
  Number num4{"1234", Sign::kMinus};
  Number zero{"0"};

  // eq signs, positive nums
  EXPECT_TRUE(num2 > num1);
  EXPECT_FALSE(num2 > num2);
  // diff signs
  EXPECT_TRUE(num1 > num3);
  EXPECT_FALSE(num3 > num1);
  // eq signs, negative nums
  EXPECT_TRUE(num3 > num4);
  EXPECT_FALSE(num3 > num3);
  // zero is the smallest positive
  EXPECT_TRUE(zero > num3);
  EXPECT_TRUE(num1 > zero);
}

TEST(MpaNumber, LessThanOp)
{
  Number num1{"123"};
  Number num2{"1234"};
  Number num3{"123", Sign::kMinus};
  Number num4{"1234", Sign::kMinus};
  Number zero{"0"};

  // eq signs, positive nums
  EXPECT_TRUE(num1 < num2);
  EXPECT_FALSE(num1 < num1);
  // diff signs
  EXPECT_TRUE(num3 < num1);
  EXPECT_FALSE(num1 < num3);
  // eq signs, negative nums
  EXPECT_TRUE(num4 < num3);
  EXPECT_FALSE(num4 < num4);
  // zero is the smallest positive
  EXPECT_TRUE(zero < num1);
  EXPECT_TRUE(num3 < zero);
}

TEST(MpaNumber, GreaterOrEqOp)
{
  Number num1{"1234"};
  Number num2{"1234", Sign::kMinus};

  Number zero{"0"};

  EXPECT_TRUE(num1 >= num1);
  EXPECT_FALSE(num2 >= num1);

  EXPECT_TRUE(num2 >= num2);
  EXPECT_FALSE(num2 >= zero);

  EXPECT_TRUE(zero >= zero);
}

TEST(MpaNumber, LessOrEqOp)
{
  Number num1{"1234"};
  Number num2{"1234", Sign::kMinus};

  Number zero{"0"};

  EXPECT_TRUE(num1 <= num1);
  EXPECT_FALSE(num1 <= num2);

  EXPECT_TRUE(num2 <= num2);
  EXPECT_FALSE(zero <= num2);

  EXPECT_TRUE(zero <= zero);
}

TEST(MpaNumber, PutIntoStreamOpPositive)
{
  Number num{"123"};
  std::ostringstream oss;

  // Positive number representation - just its' value
  oss << num;
  std::string res = oss.str();
  EXPECT_EQ("123", res);
}

TEST(MpaNumber, PutIntoStreamOpNegative)
{
  Number num{"123", Sign::kMinus};
  std::ostringstream oss;

  // Negative number representation with '-' sign in front
  oss << num;
  std::string res = oss.str();
  EXPECT_EQ("-123", res);
}

TEST(MpaNumber, VerifyNumber_EmptyValue)
{
  EXPECT_THROW(mpa::core::VerifyNumber(""), std::runtime_error);
}

TEST(MpaNumber, VerifyNumber_PositiveHasNonDigitsSymbols)
{
  EXPECT_THROW(mpa::core::VerifyNumber("1-234"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("12a34"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("abCd"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("$123\\"), std::runtime_error);
}

TEST(MpaNumber, VerifyNumber_NegativeHasNonDigitsSymbols)
{
  EXPECT_THROW(mpa::core::VerifyNumber("--234"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("-12a34"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("-abCd"), std::runtime_error);
  EXPECT_THROW(mpa::core::VerifyNumber("-$\\"), std::runtime_error);
}

TEST(MpaNumber, VerifyNumber_PositiveValueCorrect)
{
  auto statements = []() {
    const Number num = mpa::core::VerifyNumber("123456789");
    EXPECT_EQ(num.value(), "123456789");
    EXPECT_EQ(num.sign(), Sign::kPlus);
  };
  EXPECT_NO_THROW(statements());
}

TEST(MpaNumber, VerifyNumber_NegativeValueCorrect)
{
  auto statements = []() {
    const Number num = mpa::core::VerifyNumber("-123456789");
    EXPECT_EQ(num.value(), "123456789");
    EXPECT_EQ(num.sign(), Sign::kMinus);
  };
  EXPECT_NO_THROW(statements());
}

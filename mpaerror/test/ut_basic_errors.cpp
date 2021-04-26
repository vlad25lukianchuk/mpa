#include <gtest/gtest.h>

#include <string>

#include "mpaexcept.h"

using mpa::error::DivisionByZero;
using mpa::error::InvalidArgument;
using mpa::error::InvalidNumber;

TEST(MpaErrors, CtrCheck)
{
  // Just call the appropriate ctr's. Come up with more
  // sophisticated tests after the module is completely designed
  const std::string message{"Error message"};

  // const std::string&
  {
    InvalidArgument err1{message};
    InvalidNumber err2{message};
    DivisionByZero err3{message};
  }

  // const char*
  {
    InvalidArgument err1{"Error message"};
    InvalidNumber err2{"Error message"};
    DivisionByZero err3{"Error message"};
  }

  // std::string&&
  {
    InvalidArgument err1{std::string{"Error message"}};
    InvalidNumber err2{std::string{"Error message"}};
    DivisionByZero err3{std::string{"Error message"}};
  }
}

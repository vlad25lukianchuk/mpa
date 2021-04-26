#include <gtest/gtest.h>

#include <string>

#include "mpalog.h"

using mpa::log::LogMessage;

TEST(Mpalog, CheckLogMessage)
{
  // Just call every available function.
  // More sophisticated implementation will come after the
  // module is completely designed
  const std::string log_message{"Log message"};
  MPADebug() << log_message << std::endl;
  MPAInfo() << log_message << std::endl;
  MPAWarning() << log_message << std::endl;
  MPANotImplemented() << log_message << std::endl;
}

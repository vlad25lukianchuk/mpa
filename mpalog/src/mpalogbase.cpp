#include "mpalogbase.h"

#include <iostream>

#include "mpalogbase.h"

namespace mpa {
namespace log {

BaseLogger::BaseLogger(std::ostream& ost) noexcept : ost_{ost} {}

std::ostream& BaseLogger::Debug() noexcept
{
  return ost_ << kDebugTag;
}

std::ostream& BaseLogger::Info() noexcept
{
  return ost_ << kInfoTag;
}

std::ostream& BaseLogger::Warning() noexcept
{
  return ost_ << kWarningTag;
}

std::ostream& BaseLogger::NotImplemented() noexcept
{
  return ost_ << kInfoTag << kOperationIsNotImplemented;
}

StandardLogger& StandardLogger::Instance()
{
  static StandardLogger instance{};
  return instance;
}

StandardLogger::StandardLogger() noexcept : BaseLogger(std::cout) {}

}  // namespace log
}  // namespace mpa

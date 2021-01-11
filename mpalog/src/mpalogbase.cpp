#include "mpalogbase.h"

#include <iostream>

namespace mpa {
namespace log {

constexpr char kDebugTag[]{"DEBUG: "};
constexpr char kInfoTag[]{"INFO: "};
constexpr char kWarningTag[]{"WARNING: "};

constexpr char kOperationIsNotImplemented[]{"Operation is not implemented! "};

BaseLogger::BaseLogger(std::ostream &ost) : ost_{ost}
{
  // TODO: check ostream
  // we check exception in ctr, everything else is noexcept
}

std::ostream &BaseLogger::Debug() noexcept
{
  return ost_ << kDebugTag;
}

std::ostream &BaseLogger::Info() noexcept
{
  return ost_ << kInfoTag;
}

std::ostream &BaseLogger::Warning() noexcept
{
  return ost_ << kWarningTag;
}

std::ostream &BaseLogger::NotImplemented() noexcept
{
  return ost_ << kInfoTag << kOperationIsNotImplemented;
}

StandardLogger &StandardLogger::Instance()
{
  static StandardLogger instance{};
  return instance;
}

StandardLogger::StandardLogger() : BaseLogger(std::cout) {}

}  // namespace log
}  // namespace mpa

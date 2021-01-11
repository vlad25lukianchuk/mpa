#include "mpalog.h"

#include <iostream>

#include "mpalogbase.h"

namespace mpa {
namespace log {
std::ostream &LogMessage(MessageType msg_type)
{
  switch (msg_type) {
    case MessageType::kDebug:
      return mpa::log::StandardLogger::Instance().Debug();
    case MessageType::kInfo:
      return mpa::log::StandardLogger::Instance().Info();
    case MessageType::kWarning:
      return mpa::log::StandardLogger::Instance().Warning();
    case MessageType::kNotImplemented:
      return mpa::log::StandardLogger::Instance().NotImplemented();
    default:
      // w/o default option gets
      // warning: control reaches end of non-void function [-Wreturn-type]
      // consider another solution
      return mpa::log::StandardLogger::Instance().Info();
  }
}
}  // namespace log
}  // namespace mpa

#ifndef MPA_MPALOG_INCLUDE_MPALOG_H_
#define MPA_MPALOG_INCLUDE_MPALOG_H_

#include <iostream>

namespace mpa {
namespace log {

enum class MessageType { kDebug, kInfo, kWarning, kNotImplemented };

std::ostream& LogMessage(MessageType msg_type);

}  // namespace log
}  // namespace mpa

#define MPADebug() LogMessage(mpa::log::MessageType::kDebug)
#define MPAInfo() LogMessage(mpa::log::MessageType::kInfo)
#define MPAWarning() LogMessage(mpa::log::MessageType::kWarning)
#define MPANotImplemented() LogMessage(mpa::log::MessageType::kNotImplemented)

#endif  // MPA_MPALOG_INCLUDE_MPALOG_H_

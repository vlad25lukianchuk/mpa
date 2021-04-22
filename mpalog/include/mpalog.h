#ifndef MPA_MPALOG_INCLUDE_MPALOG_H_
#define MPA_MPALOG_INCLUDE_MPALOG_H_

#include <iostream>

#ifdef _WIN32
#ifdef MPA_BUILD_LOG_LIB
#define MPA_LOG_EXPORT __declspec(dllexport)
#else
#define MPA_LOG_EXPORT __declspec(dllimport)
#endif
#else
#define MPA_LOG_EXPORT
#endif

namespace mpa {
namespace log {

enum class MPA_LOG_EXPORT MessageType {
  kDebug,
  kInfo,
  kWarning,
  kNotImplemented
};

MPA_LOG_EXPORT std::ostream& LogMessage(MessageType msg_type);

}  // namespace log
}  // namespace mpa

#define MPADebug() LogMessage(mpa::log::MessageType::kDebug)
#define MPAInfo() LogMessage(mpa::log::MessageType::kInfo)
#define MPAWarning() LogMessage(mpa::log::MessageType::kWarning)
#define MPANotImplemented() LogMessage(mpa::log::MessageType::kNotImplemented)

#endif  // MPA_MPALOG_INCLUDE_MPALOG_H_

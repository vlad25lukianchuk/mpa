#ifndef MPA_MPALOG_SRC_MPALOGUTILS_H_
#define MPA_MPALOG_SRC_MPALOGUTILS_H_

#define MPA_NO_COPY(cls)    \
  cls(const cls&) = delete; \
  cls& operator=(const cls&) = delete;

#define MPA_NO_MOVE(cls) \
  cls(cls&&) = delete;   \
  cls& operator=(cls&&) = delete;

namespace mpa {
namespace log {

constexpr char kDebugTag[]{"DEBUG: "};
constexpr char kInfoTag[]{"INFO: "};
constexpr char kWarningTag[]{"WARNING: "};
constexpr char kOperationIsNotImplemented[]{"Operation is not implemented! "};

}  // namespace log
}  // namespace mpa

#endif  // MPA_MPALOG_SRC_MPALOGUTILS_H_

#ifndef MPA_MPALOG_SRC_MPALOGBASE_H_
#define MPA_MPALOG_SRC_MPALOGBASE_H_

#include <iostream>

#include "mpalogutils.h"

namespace mpa {
namespace log {

class BaseLogger {
 public:
  MPA_NO_COPY(BaseLogger)
  MPA_NO_MOVE(BaseLogger)

  explicit BaseLogger(std::ostream& ost) noexcept;
  virtual ~BaseLogger() = default;

  // TODO: currently noexcept, exception handling
  // will be added later
  std::ostream& Debug() noexcept;
  std::ostream& Info() noexcept;
  std::ostream& Warning() noexcept;
  std::ostream& NotImplemented() noexcept;

 protected:
  std::ostream& ost_;
};

class StandardLogger : public BaseLogger {
 public:
  MPA_NO_COPY(StandardLogger)
  MPA_NO_MOVE(StandardLogger)

  ~StandardLogger() = default;

  static StandardLogger& Instance();

 private:
  StandardLogger() noexcept;
};

}  // namespace log
}  // namespace mpa

#endif  // MPA_MPALOG_SRC_MPALOGBASE_H_

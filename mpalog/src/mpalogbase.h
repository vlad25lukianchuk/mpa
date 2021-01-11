#ifndef MPA_MPALOG_SRC_MPALOGBASE_H_
#define MPA_MPALOG_SRC_MPALOGBASE_H_

#include <iostream>

// TODO: implement more robust way, move to utils
#define MPA_NO_COPY(cls)    \
  cls(const cls&) = delete; \
  cls& operator=(const cls&) = delete;

#define MPA_NO_MOVE(cls) \
  cls(cls&&) = delete;   \
  cls& operator=(cls&&) = delete;

namespace mpa {
namespace log {

class BaseLogger {
 public:
  MPA_NO_COPY(BaseLogger)
  MPA_NO_MOVE(BaseLogger)

  explicit BaseLogger(std::ostream& ost);
  virtual ~BaseLogger() = default;

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
  StandardLogger();
};

}  // namespace log
}  // namespace mpa

#endif  // MPA_MPALOG_SRC_MPALOGBASE_H_

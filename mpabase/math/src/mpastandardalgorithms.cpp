#include "mpastandardalgorithms.h"

#include <memory>

#include "mpacoreutils.h"
#include "mpanumber.h"
#include "mpastandardalgorithmsimpl.h"

namespace mpa {
namespace math {
namespace impl {

StandardAlgorithms::StandardAlgorithms()
    : impl_{std::make_unique<StandardAlgorithmsImpl>()}
{
}

core::Number StandardAlgorithms::Add(const std::string& lhs,
                                     const std::string& rhs) const noexcept
{
  return lhs.size() > rhs.size() ? core::Number{impl_->Add(lhs, rhs)}
                                 : core::Number{impl_->Add(rhs, lhs)};
}

core::Number StandardAlgorithms::Subtract(const std::string& lhs,
                                          const std::string& rhs) const noexcept
{
  return core::IsAbsGreaterOrEqual(lhs, rhs)
             ? core::Number{impl_->Subtract(lhs, rhs)}
             : -core::Number{impl_->Subtract(rhs, lhs)};
}

core::Number StandardAlgorithms::Multiply(const std::string& lhs,
                                          const std::string& rhs) const noexcept
{
  return lhs.size() > rhs.size() ? core::Number{impl_->Multiply(lhs, rhs)}
                                 : core::Number{impl_->Multiply(rhs, lhs)};
}

core::Number StandardAlgorithms::Divide(const std::string& lhs,
                                        const std::string& rhs) const noexcept
{
  return core::Number{impl_->Divide(lhs, rhs)};
}

core::Number StandardAlgorithms::Reminder(const std::string& lhs,
                                          const std::string& rhs) const noexcept
{
  return core::Number{impl_->Reminder(lhs, rhs)};
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

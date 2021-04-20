#include "mpaintegeralgorithmsfactory.h"

#include <memory>

#include "mpastandardalgorithms.h"

namespace mpa {
namespace math {
namespace impl {

AlgorithmsAbstract& IntegerAlgorithmsFactory::CreateStandard() noexcept
{
  return *algo_;
}

IntegerAlgorithmsFactory::IntegerAlgorithmsFactory()
    : algo_{std::make_unique<StandardAlgorithms>()}
{
}

}  // namespace impl
}  // namespace math
}  // namespace mpa

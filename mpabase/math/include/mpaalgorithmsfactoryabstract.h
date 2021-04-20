#ifndef MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSFACTORYABSTRACT_H_
#define MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSFACTORYABSTRACT_H_

#include <memory>

#include "mpaalgorithmsabstract.h"

namespace mpa {
namespace math {
namespace impl {

class AlgorithmsFactoryAbstract {
 public:
  virtual ~AlgorithmsFactoryAbstract() = default;
  virtual AlgorithmsAbstract& CreateStandard() noexcept = 0;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPAALGORITHMSFACTORYABSTRACT_H_

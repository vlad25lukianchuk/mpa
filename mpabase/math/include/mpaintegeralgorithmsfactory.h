#ifndef MPA_MPABASE_MATH_INCLUDE_MPASTANDARDINTEGERALGOFACTORY_H_
#define MPA_MPABASE_MATH_INCLUDE_MPASTANDARDINTEGERALGOFACTORY_H_

#include <memory>

#include "mpaalgorithmsfactoryabstract.h"
#include "singleton.h"

namespace mpa {
namespace math {
namespace impl {

class IntegerAlgorithmsFactory : public AlgorithmsFactoryAbstract,
                                 public Singleton<IntegerAlgorithmsFactory> {
 public:
  AlgorithmsAbstract& CreateStandard() noexcept override;

 private:
  IntegerAlgorithmsFactory();
  std::unique_ptr<AlgorithmsAbstract> algo_;

  friend class Singleton<IntegerAlgorithmsFactory>;
};

}  // namespace impl
}  // namespace math
}  // namespace mpa

#endif  // MPA_MPABASE_MATH_INCLUDE_MPASTANDARDINTEGERALGOFACTORY_H_

#ifndef MPA_MPABASE_CORE_INCLUDE_MPACOREDEFS_H_
#define MPA_MPABASE_CORE_INCLUDE_MPACOREDEFS_H_

#include "mpanumber.h"

// TODO: mb move to global module
// Avoid "unused parameter" warnings
#define MPA_UNUSED(x) (void)x;

namespace mpa {
namespace core {

// shorthand definition of number zero
static const Number kZero{"0"};

// shorthand definition of number one (positive)
static const Number kOne{"1", Sign::kPlus};

}  // namespace core
}  // namespace mpa

#endif  // MPA_MPABASE_CORE_INCLUDE_MPACOREDEFS_H_

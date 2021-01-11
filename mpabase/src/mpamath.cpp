#include "mpamath.h"

using std::string;

namespace mpa {
namespace math {

constexpr int kBase{10};

// TODO: works, but not nice
string Add(const string& larger, const string& smaller) noexcept
{
  string reverse_res;
  reverse_res.reserve(larger.size());

  int rest{0};
  int dec{0};
  auto l_it = larger.rbegin();

  // add smaller number to the larger
  for (auto s_it = smaller.rbegin(); s_it != smaller.rend(); ++s_it) {
    const int sum = ToDec(*l_it) + ToDec(*s_it) + dec;
    rest = sum % kBase;
    dec = sum / kBase;
    reverse_res.push_back(ToChar(rest));
    ++l_it;
  }

  // correctly process the rest of larger if any
  while (l_it != larger.rend()) {
    const int sum = ToDec(*l_it) + dec;
    rest = sum % kBase;
    dec = sum / kBase;
    reverse_res.push_back(ToChar(rest));
    ++l_it;
  }

  // add additional 'one' at the end if needed
  if (dec) {
    reverse_res.push_back(ToChar(dec));
  }

  return {reverse_res.rbegin(), reverse_res.rend()};
}

string Substract(const string& lhs, const string& rhs) noexcept {}

}  // namespace math
}  // namespace mpa

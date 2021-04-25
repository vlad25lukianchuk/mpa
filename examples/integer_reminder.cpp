#include <iostream>
#include <stdexcept>

#include "mpainteger.h"

using Int_t = mpa::Integer;

void CalculateAndPrint(const Int_t& lhs, const Int_t& rhs)
{
  std::cout << lhs << " % " << rhs << " = " << lhs % rhs << std::endl;
}

int main()
{
  Int_t lhs{"625"};
  Int_t rhs{"25"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"627"};
  rhs = Int_t{"25"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"0"};
  rhs = Int_t{"123"};
  CalculateAndPrint(lhs, rhs);

  // if negative, minus sign should go at the very beginning
  // reminder works with signs the same way as the other operations
  lhs = Int_t{"-123"};
  rhs = Int_t{"123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"-123"};
  rhs = Int_t{"-123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"123"};
  rhs = Int_t{"-123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"123"};
  rhs = Int_t{"0"};
  std::cout << lhs << " % " << rhs << " = " << std::endl;
  try {
    // devision (reminder) by zero
    auto result = lhs / rhs;
  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }

  return 0;
}

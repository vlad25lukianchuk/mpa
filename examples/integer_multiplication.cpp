#include <iostream>
#include <stdexcept>

#include "mpainteger.h"

using Int_t = mpa::Integer;

void CalculateAndPrint(const Int_t& lhs, const Int_t& rhs)
{
  std::cout << lhs << " * " << rhs << " = " << lhs * rhs << std::endl;
}

int main()
{
  Int_t lhs{"12345678"};
  Int_t rhs{"555"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"1234566778901231231231231231231231231231231231231"};
  rhs = Int_t{"12345667789012312312312312312312312312312312312311111"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"999"};
  rhs = Int_t{"999"};
  CalculateAndPrint(lhs, rhs);

  // this will be trimmed to just '0'
  lhs = Int_t{"0"};
  // this will be zero as well
  rhs = Int_t{"0"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"0"};
  rhs = Int_t{"1"};
  CalculateAndPrint(lhs, rhs);

  // if negative, minus sign should go at the very beginning
  lhs = Int_t{"-123"};
  rhs = Int_t{"123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"-123"};
  rhs = Int_t{"-123"};
  CalculateAndPrint(lhs, rhs);

  return 0;
}

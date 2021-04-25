#include <iostream>
#include <stdexcept>
#include <string>

#include "mpainteger.h"

using Int_t = mpa::Integer;

void CalculateAndPrint(const Int_t& lhs, const Int_t& rhs)
{
  std::cout << lhs << " - " << rhs << " = " << lhs - rhs << std::endl;
}

void CatchIncorrectNumbers(const std::string& num_str)
{
  try {
    const Int_t num{num_str};
  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
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
  lhs = Int_t{"000"};
  // this will be zero as well
  rhs = Int_t{"-00"};
  CalculateAndPrint(lhs, rhs);

  // if negative, minus sign should go at the very beginning
  lhs = Int_t{"-123"};
  rhs = Int_t{"123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"-123"};
  rhs = Int_t{"-123"};
  CalculateAndPrint(lhs, rhs);

  lhs = Int_t{"123"};
  rhs = Int_t{"-123"};
  CalculateAndPrint(lhs, rhs);

  // values '000-123' are malformed
  // values '-000123' are ok, trimmed to '123' with negative sign
  CatchIncorrectNumbers("000-123");

  return 0;
}

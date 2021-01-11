#include <iostream>

#include "mpainteger.h"

int main()
{
  mpa::Integer first{"123456"};
  mpa::Integer second{"2876"};

  std::cout << first + second << std::endl;

  first = mpa::Integer{
      "1234566778901231231231231231231231231231231231231"
      "1234566778901231231231231231231231231231231231231"
      "1234566778901231231231231231231231231231231231231"};
  second = mpa::Integer{
      "1234566778901231231231231231231231231231231231231"
      "1234566778901231231231231231231231231231231231231"
      "1234566778901231231231231231231231231231231231231"
      "1234566778901231231231231231231231231231231231231"};

  std::cout << first + second << std::endl;

  first = mpa::Integer("99");
  second = mpa::Integer("99");

  std::cout << first + second << std::endl;

  return 0;
}

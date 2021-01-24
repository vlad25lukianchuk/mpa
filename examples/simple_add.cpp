#include <iostream>

#include "mpainteger.h"

int main()
{
  mpa::Integer first{"123456"};
  mpa::Integer second{"2876"};
  const auto result = first + second;
  std::cout << first << " + " << second << " = " << result << std::endl;
  std::cout << result << " - " << second << " = " << result - second << std::endl;
  std::cout << result << " - " << first << " = " << result - first << std::endl;

  first = mpa::Integer{
      "1234566778901231231231231231231231231231231231231"};
  second = mpa::Integer{
      "1234566778901231231231231231231231231231231231231"};
  std::cout << first << " + " << second << " = " << first + second << std::endl;
  std::cout << first << " * " << second << " = " << first * second << std::endl;

  first = mpa::Integer("99");
  second = mpa::Integer("99");
  std::cout << first << " + " << second << " = " << first + second << std::endl;


  first = mpa::Integer("-10");
  second = mpa::Integer("11");
  std::cout << first << " + " << second << " = " << first + second << std::endl;
  std::cout << first << " * " << second << " = " << first * second << std::endl;

  first = mpa::Integer("20");
  second = mpa::Integer("10");
  std::cout << first << " - " << second << " = " << first - second << std::endl;

  std::cout << first << " * " << second << " = " << first * second << std::endl;

  first = mpa::Integer{"9899898912345678981"};
  second = mpa::Integer{"98998989123456789"};
  std::cout << first << " / " << second << " = " << first / second << std::endl;
  std::cout << first << " % " << second << " = " << first % second << std::endl;

  return 0;
}

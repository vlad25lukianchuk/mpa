#include "mpaexcept.h"

namespace mpa {
namespace error {

constexpr char kInvalidArgumentErr[]{"Invalid argument error: "};
constexpr char kInvalidNumberErr[]{"Invalid number error: "};
constexpr char kDomainErr[]{"Domain error: "};

InvalidArgument::InvalidArgument(const std::string& msg)
    : std::invalid_argument{kInvalidArgumentErr + msg}
{
}

InvalidArgument::InvalidArgument(std::string&& msg)
    : std::invalid_argument{kInvalidArgumentErr + msg}
{
}

InvalidArgument::InvalidArgument(const char* msg)
    : std::invalid_argument{kInvalidArgumentErr + std::string{msg}}
{
}

InvalidNumber::InvalidNumber(const std::string& msg)
    : std::logic_error{kInvalidNumberErr + msg}
{
}

InvalidNumber::InvalidNumber(std::string&& msg)
    : std::logic_error{kInvalidNumberErr + msg}
{
}

InvalidNumber::InvalidNumber(const char* msg)
    : std::logic_error{kInvalidNumberErr + std::string{msg}}
{
}

DivisionByZero::DivisionByZero(const std::string& msg)
    : std::domain_error{kDomainErr + msg}
{
}

DivisionByZero::DivisionByZero(std::string&& msg)
    : std::domain_error{kDomainErr + msg}
{
}

DivisionByZero::DivisionByZero(const char* msg)
    : std::domain_error{kDomainErr + std::string{msg}}
{
}

}  // namespace error
}  // namespace mpa

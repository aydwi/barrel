#ifndef HELPERS_H_
#define HELPERS_H_

#include <type_traits>

//
// Get the integral "underlying type" of an enumerator from a scoped enumeration
//
template <typename Enum>
constexpr std::enable_if_t<std::is_enum<Enum>::value, std::underlying_type_t<Enum>> enumUnderlyingType(Enum const val) // https://docs.microsoft.com/en-us/cpp/standard-library/enable-if-class
{
    return static_cast<std::underlying_type_t<Enum>>(val);
}

#endif
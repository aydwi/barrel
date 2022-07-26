#ifndef UTILS_H__
#define UTILS_H__

#include <concepts>
#include <type_traits>

template <typename E>
concept EnumType = std::is_enum_v<E>; // REF::UTILS_H__001

//
// Get the integral "underlying type" of an enumerator from a scoped enumeration
//
template <EnumType E>
constexpr std::underlying_type_t<E> enumUnderlyingType(E const underlying_type) {
    return static_cast<std::underlying_type_t<E>>(underlying_type);
}

#endif
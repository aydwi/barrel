#ifndef BARREL_H__
#define BARREL_H__

#include "types.h"
#include "utils.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <string>

inline extern std::string const OPT_PREFIX{"--"};

namespace Meta {
//
// The latest compatible version of Homebrew with this release
//
inline extern std::string const _version{"Homebrew 3.5.4"};
} // namespace Meta

template <EnumType E>
class BrewCommand {
private:
    E type_;
    std::string head_;

public:
    template <typename S = std::string, typename... Args>
    BrewCommand(E type, S const& head, Args... args);
};

template <EnumType E>
template <typename S, typename... Args>
BrewCommand<E>::BrewCommand(E type, S const& head, Args... args)
    : type_(type), head_(head){};

#endif
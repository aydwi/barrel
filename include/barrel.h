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
#include <type_traits>

namespace Spec {
//
// The latest compatible version of Homebrew with this release
//
inline extern std::string const _version{"Homebrew 3.5.4"};
} // namespace Spec

template <EnumType E>
class BrewCommand {
private:
    E cmd_;

public:
    template <typename... Args>
    explicit BrewCommand(E cmd, Args... args);
};

template <EnumType E>
template <typename... Args>
BrewCommand<E>::BrewCommand(E cmd, Args... args) : cmd_(cmd){};

#endif
#ifndef BARREL_H__
#define BARREL_H__

#include "spec.h"
#include "types.h"
#include "utils.h"

#include <cstddef>
#include <cstdint>
#include <queue>

class Brew {};

template <EnumType E>
class BrewCommand : public Brew {
private:
    E cmd_;
    std::string head_;

public:
    explicit BrewCommand(E cmd);

    template <typename... Args>
    explicit BrewCommand(E cmd, Args... args);

public:
    std::string const& getCommandHead() const; // TIP::BARREL_H__001
};

template <EnumType E>
BrewCommand<E>::BrewCommand(E cmd) : cmd_(cmd), head_(getBrewCommandHead(cmd)){};

template <EnumType E>
template <typename... Args>
BrewCommand<E>::BrewCommand(E cmd, Args... args) : cmd_(cmd), head_(getBrewCommandHead(cmd)){};

template <EnumType E>
std::string const& BrewCommand<E>::getCommandHead() const {
    return head_;
};

#endif

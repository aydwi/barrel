#ifndef BARREL_H__
#define BARREL_H__

#include "spec.h"
#include "types.h"
#include "utils.h"

#include <cstddef>
#include <cstdint>
#include <queue>

using namespace std::string_literals;

class Brew {
private:
    inline static std::string spec_version_{BarrelSpec::_brew_version};

    std::string install_path_;
    std::string install_version_;
    bool is_installed_;

public:
    explicit Brew();
    explicit Brew(std::string const);

public:
    std::string const& getInstallPath() const; // TIP::BARREL_H__001
    std::string const& getInstallVersion() const;
    bool getInstallStatus() const;
};

Brew::Brew(std::string const install_path) : install_path_(install_path){/*do logic*/};

Brew::Brew() : Brew{BrewSpec::_brew_default_path} {}; // TIP::BARREL_H__002

bool Brew::getInstallStatus() const {
    return is_installed_;
}
std::string const& Brew::getInstallPath() const {
    return install_path_;
}
std::string const& Brew::getInstallVersion() const {
    return install_version_;
}

template <EnumType E>
class BrewCommand : public Brew {
private:
    E cmd_;
    std::string head_;

public:
    explicit BrewCommand(E);

    template <typename... Args>
    explicit BrewCommand(E, Args...);

public:
    std::string const& getCommandHead() const;
};

template <EnumType E>
template <typename... Args>
BrewCommand<E>::BrewCommand(E cmd, Args... args) : cmd_(cmd), head_(getBrewCommandHead(cmd)){};

template <EnumType E>
BrewCommand<E>::BrewCommand(E cmd) : cmd_(cmd), head_(getBrewCommandHead(cmd)){};

template <EnumType E>
std::string const& BrewCommand<E>::getCommandHead() const {
    return head_;
}

#endif

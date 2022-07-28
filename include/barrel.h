/*!
 * This file is part of Barrel, a header-only C++ library that provides
 * programmatic access to the Homebrew command line interface.
 *
 * Copyright (C) 2022 aydwi <contact@aydwi.com>
 *
 * Barrel is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BARREL_H__
#define BARREL_H__

#include "command.h"
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
    std::string const& getInstallPath() const; // CUE::BARREL_H__001
    std::string const& getInstallVersion() const;
    bool getInstallStatus() const;
};

Brew::Brew(std::string const install_path) : install_path_(install_path){};

Brew::Brew() : Brew{BrewSpec::_brew_default_path} {}; // CUE::BARREL_H__002

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

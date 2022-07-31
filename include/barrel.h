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

#include "proc.h"
#include "spec.h"
#include "types.h"
#include "utils.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <queue>

using namespace std::string_literals;

class Brew {
private:
    BrewTargetArch target_arch_;
    std::string install_path_;
    std::string install_version_;

private:
    void validateBrewInstallation();

public:
    inline static bool is_installed{false};
    inline static bool skip_validation{false};
    inline static std::string const spec_version{BarrelSpec::_BREW_VERSION};

public:
    explicit Brew();
    explicit Brew(BrewTargetArch);
    explicit Brew(std::string const);
    explicit Brew(BrewTargetArch, std::string const);

public:
    std::string const& getInstallPath() const; // CUE::BARREL_H__001
    std::string const& getInstallVersion() const;
};

void Brew::validateBrewInstallation() {
    std::string const check_path =
        install_path_ + LE_SPACER + getBrewCommandHead(BrewCommandType::Builtin::VERSION);

    BarrelCmd::Proc proc(check_path, BarrelCmd::Stream::STDOUT_STDERR);
    proc.execute();

    if (proc.getExitStatus() == EXIT_SUCCESS) {
        Brew::is_installed = true;
        std::string const dump = proc.getStreamDump();
        install_version_ = {dump.begin(), std::find(dump.begin(), dump.end(), '\n')};
    } else {
        throw std::runtime_error(
            "Brew::validateBrewInstallation(): Homebrew installation failed to validate!");
    }
}

Brew::Brew(BrewTargetArch target_arch, std::string const install_path)
    : target_arch_(target_arch), install_path_(install_path) {
    if (Brew::skip_validation)
        return;
    validateBrewInstallation();
};

Brew::Brew(std::string const install_path) : Brew{BrewTargetArch::X86_64, install_path} {};

Brew::Brew(BrewTargetArch target_arch)
    : Brew{target_arch, target_arch == BrewTargetArch::X86_64 ? BrewSpec::_BREW_DEFAULT_PATH_X86_64
                                                              : BrewSpec::_BREW_DEFAULT_PATH_ARM64} {};

Brew::Brew() : Brew{BrewTargetArch::X86_64, BrewSpec::_BREW_DEFAULT_PATH_X86_64} {}; // CUE::BARREL_H__002

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

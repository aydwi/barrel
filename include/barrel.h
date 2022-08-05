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

/*! \file  barrel.h
 *  \brief The primary header exposed by Barrel. Provides the entire core functionality
 *         the library.
 */

// TODO: Correct broken inheritance and introduce proper command types

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
#include <string>
#include <string_view>
#include <utility>
#include <variant>

#define BAD_EXIT_ST INT_MAX & 0xff

using namespace std::string_literals;

template <typename>
struct FalseType : std::false_type {};

/*! \brief Set up a Homebrew execution environment.
 *         Further, customize and validate the execution environment.
 */
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
    /*! \brief Default constructor for Brew.
     *
     *  The simplest way to construct a Brew object. Barrel defaults the
     *  target architecture to BrewTargetArch::X86_64 and correspondingly
     *  the Homebrew installation path to BrewSpec::_BREW_DEFAULT_PATH_X86_64.
     *
     *  \sa BrewSpec
     */
    Brew();

    /*! \brief A constructor for Brew, which allows you to specify your target
     *         architecture. Homebrew installation path is set to the default
     *         path for this architecture.
     *
     *  \param target_arch Target architecture
     *
     *  \sa BrewSpec
     */
    explicit Brew(BrewTargetArch);

    /*! \brief A constructor for Brew, which allows you to specify a custom
     *         location for your Homebrew installation, specifically the `brew`
     *         binary. Barrel defaults the target architecture to BrewTargetArch::X86_64.
     *
     *  \param install_path Custom `brew` installation path
     *
     *  \sa BrewSpec
     */
    explicit Brew(std::string const&);

    /*! \brief A constructor for Brew, which allows you to specify both your target
     *         architecture and a custom path for your Homebrew installation.
     *
     *  \param target_arch Target architecture
     *  \param install_path Custom `brew` installation path
     *
     *  \sa BrewSpec
     */
    Brew(BrewTargetArch, std::string const&);

public:
    std::string const& getInstallPath() const; // BARREL_H__001
    std::string const& getInstallVersion() const;
};

void Brew::validateBrewInstallation() {
    std::string const check_path =
        install_path_ + LE_SPACER + getCommandHead(BrewCommandType::Builtin::VERSION);

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

Brew::Brew(BrewTargetArch target_arch, std::string const& install_path)
    : target_arch_(target_arch), install_path_(install_path) {
    if (Brew::skip_validation)
        return;
    validateBrewInstallation();
};

Brew::Brew(std::string const& install_path) : Brew{BrewTargetArch::X86_64, install_path} {};

Brew::Brew(BrewTargetArch target_arch)
    : Brew{target_arch, target_arch == BrewTargetArch::X86_64 ? BrewSpec::_BREW_DEFAULT_PATH_X86_64
                                                              : BrewSpec::_BREW_DEFAULT_PATH_ARM64} {};

Brew::Brew() : Brew{BrewTargetArch::X86_64, BrewSpec::_BREW_DEFAULT_PATH_X86_64} {}; // BARREL_H__002

std::string const& Brew::getInstallPath() const {
    return install_path_;
}
std::string const& Brew::getInstallVersion() const {
    return install_version_;
}

/*! \brief Work with Homebrew commands in your program including set-up,
 *         execution and retrieval of the results of arbitrary Homebrew
 *         commands. The template class must be instantiated with an
 *         appropriate type from the namespace ::BrewCommandType.
 */
template <EnumType E>
class BrewCommand {
private:
    E cmd_;
    std::string head_{};
    std::string chain_{};
    std::string stream_dump_{};
    int exit_status_{BAD_EXIT_ST};

private:
    std::queue<std::variant<const char*, std::string>> q_{};

public:
    /*! \brief A variadic constructor for BrewCommand.
     *
     *  This is the singular constructor offered by BrewCommand. Due
     *  to it being variadic, an arbitrary number of arguments can be
     *  passed to the constructor. Barrel expects you to pass a chain
     *  of Homebrew arguments that follow your choice of command thereby
     *  allowing any possible Homebrew command to be executed.
     *
     *
     *  \param brew An object of type ::Brew
     *  \param cmd The brew command you want to execute
     *  \param args A parameter pack representing in order,
     *              the chain of options/text that follows
     *              *cmd* as prescribed by Homebrew. The
     *              following object types are allowed in the
     *              parameter pack: `const char*`, `std::string`
     *
     *  \sa BrewCommandType
     */
    template <typename... Args>
    BrewCommand(Brew const&, E, Args...);

public:
    std::string const& getHead() const;
    std::string const& getChain() const;

public:
    std::string const& getStreamDump() const;
    int getExitStatus() const;

public:
    void execute();
};

template <EnumType E>
template <typename... Args>
BrewCommand<E>::BrewCommand(Brew const& brew, E cmd, Args... args)
    : cmd_(cmd), head_(getCommandHead(cmd)), chain_(brew.getInstallPath()) {
    (q_.push(std::forward<Args>(args)), ...);
    chain_ += LE_SPACER + head_;

    while (!q_.empty()) {
        std::visit(
            [&chain_ = chain_](auto&& arg) {
                using Tt = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<Tt, const char*> || std::is_same_v<Tt, std::string>)
                    chain_ += LE_SPACER + arg;
                // Consider string_view too
                else
                    static_assert(FalseType<Tt>::value, "Barrel Dev Error: Fix this if-constexpr to make it "
                                                        "exhaustive with the types q_ supports");
            },
            q_.front());
        q_.pop();
    }
};

template <EnumType E>
std::string const& BrewCommand<E>::getHead() const {
    return head_;
}

template <EnumType E>
std::string const& BrewCommand<E>::getChain() const {
    return chain_;
}

template <EnumType E>
std::string const& BrewCommand<E>::getStreamDump() const {
    return stream_dump_;
}

template <EnumType E>
int BrewCommand<E>::getExitStatus() const {
    return exit_status_;
}

template <EnumType E>
void BrewCommand<E>::execute() {
    BarrelCmd::Proc proc(chain_, BarrelCmd::Stream::STDOUT_STDERR);
    proc.execute();
    stream_dump_ = proc.getStreamDump();
    exit_status_ = proc.getExitStatus();
}

#endif

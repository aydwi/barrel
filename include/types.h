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

/*! \file  types.h
    \brief An internal header used by Barrel. Maintains core types used by the
           library.
*/

#ifndef TYPES_H__
#define TYPES_H__

#include <string>
#include <unordered_map>

using namespace std::string_literals; // TYPES_H__001

/*! \brief Enumeration of target machine architectures.
 */
enum class BrewTargetArch {
    X86_64, /*!< 64 bit Intel environment */
    ARM64,  /*!< 64 bit ARM environment */
};

/*! \brief Collection of Homebrew command categories.
 */
namespace BrewCommandType {
enum class Builtin;    /*!< "Built-in" command type */
enum class BuiltinDev; /*!< "Built-in developer" command type */
enum class External;   /*!< "External" command type */
};                     // namespace BrewCommandType

// clang-format off

/*! \brief Enumeration of built-in commands.
 */
enum class BrewCommandType::Builtin {
    CACHE = 0x1,
    CASKROOM,
    CELLAR,
    ENV,
    PREFIX,
    REPOSITORY,
    VERSION,
    ANALYTICS,
    AUTOREMOVE,
    CASKS,
    CLEANUP,
    COMMANDS,
    COMPLETIONS,
    CONFIG,
    DEPS,
    DESC,
    DEVELOPER,
    DOCTOR,
    FETCH,
    FORMULAE,
    GIST_LOGS,
    HELP,
    HOME,
    INFO,
    INSTALL,
    LEAVES,
    LINK,
    LIST,
    LOG,
    MIGRATE,
    MISSING,
    OPTIONS,
    OUTDATED,
    PIN,
    POSTINSTALL,
    READALL,
    REINSTALL,
    SEARCH,
    SHELLENV,
    TAP,
    TAP_INFO,
    UNINSTALL,
    UNLINK,
    UNPIN,
    UNTAP,
    UPDATE,
    UPDATE_REPORT,
    UPDATE_RESET,
    UPGRADE,
    USES,
    VENDOR_INSTALL,
};

/*! \brief Enumeration of built-in developer commands.
 */
enum class BrewCommandType::BuiltinDev {
    AUDIT = 0x1,
    BOTTLE,
    BUMP,
    BUMP_CASK_PR,
    BUMP_FORMULA_PR,
    BUMP_REVISION,
    BUMP_UNVERSIONED_CASKS,
    CAT,
    COMMAND,
    CREATE,
    DISPATCH_BUILD_BOTTLE,
    EDIT,
    EXTRACT,
    FORMULA,
    GENERATE_MAN_COMPLETIONS,
    INSTALL_BUNDLER_GEMS,
    IRB,
    LINKAGE,
    LIVECHECK,
    PR_AUTOMERGE,
    PR_PUBLISH,
    PR_PULL,
    PR_UPLOAD,
    PROF,
    RELEASE,
    RUBOCOP,
    RUBY,
    SH,
    SPONSORS,
    STYLE,
    TAP_NEW,
    TEST,
    TESTS,
    TYPECHECK,
    UNBOTTLED,
    UNPACK,
    UPDATE_LICENSE_DATA,
    UPDATE_MAINTAINERS,
    UPDATE_PYTHON_RESOURCES,
    UPDATE_TEST,
    VENDOR_GEMS,
};

/*! \brief Enumeration of external commands.
 */
enum class BrewCommandType::External {
    ASPELL_DICTIONARIES = 0x1,
    DETERMINE_REBOTTLE_RUNNERS,
    POSTGRESQL_UPGRADE_DATABASE,
};

// clang-format on

/*! \brief A (namespace-like) type that declares mappings of Homebrew commands
 *         to command "heads".
 *
 * A command "head" is string representation of the first word of a Homebrew command.
 * For example, in `brew --cache`, `"--cache"` is the command head.
 */
struct BrewCommandHead {
    static std::unordered_map<BrewCommandType::Builtin, std::string> const Builtin;
    static std::unordered_map<BrewCommandType::BuiltinDev, std::string> const BuiltinDev;
    static std::unordered_map<BrewCommandType::External, std::string> const External;
};

// clang-format off

/*! \brief Mapping of built-in commands to their respective command heads.
 *         \sa BrewCommandType::Builtin, BrewCommandHead
 */
std::unordered_map<BrewCommandType::Builtin, std::string> const BrewCommandHead::Builtin {
    { BrewCommandType::Builtin::CACHE,                          "--cache"s },
    { BrewCommandType::Builtin::CASKROOM,                       "--caskroom"s },
    { BrewCommandType::Builtin::CELLAR,                         "--cellar"s },
    { BrewCommandType::Builtin::ENV,                            "--env"s },
    { BrewCommandType::Builtin::PREFIX,                         "--prefix"s },
    { BrewCommandType::Builtin::REPOSITORY,                     "--repository"s },
    { BrewCommandType::Builtin::VERSION,                        "--version"s },
    { BrewCommandType::Builtin::ANALYTICS,                      "analytics"s },
    { BrewCommandType::Builtin::AUTOREMOVE,                     "autoremove"s },
    { BrewCommandType::Builtin::CASKS,                          "casks"s },
    { BrewCommandType::Builtin::CLEANUP,                        "cleanup"s },
    { BrewCommandType::Builtin::COMMANDS,                       "commands"s },
    { BrewCommandType::Builtin::COMPLETIONS,                    "completions"s },
    { BrewCommandType::Builtin::CONFIG,                         "config"s },
    { BrewCommandType::Builtin::DEPS,                           "deps"s },
    { BrewCommandType::Builtin::DESC,                           "desc"s },
    { BrewCommandType::Builtin::DEVELOPER,                      "developer"s },
    { BrewCommandType::Builtin::DOCTOR,                         "doctor"s },
    { BrewCommandType::Builtin::FETCH,                          "fetch"s },
    { BrewCommandType::Builtin::FORMULAE,                       "formulae"s },
    { BrewCommandType::Builtin::GIST_LOGS,                      "gist-logs"s },
    { BrewCommandType::Builtin::HELP,                           "help"s },
    { BrewCommandType::Builtin::HOME,                           "home"s },
    { BrewCommandType::Builtin::INFO,                           "info"s },
    { BrewCommandType::Builtin::INSTALL,                        "install"s },
    { BrewCommandType::Builtin::LEAVES,                         "leaves"s },
    { BrewCommandType::Builtin::LINK,                           "link"s },
    { BrewCommandType::Builtin::LIST,                           "list"s },
    { BrewCommandType::Builtin::LOG,                            "logv"s },
    { BrewCommandType::Builtin::MIGRATE,                        "migrate"s },
    { BrewCommandType::Builtin::MISSING,                        "missing"s },
    { BrewCommandType::Builtin::OPTIONS,                        "options"s },
    { BrewCommandType::Builtin::OUTDATED,                       "outdated"s },
    { BrewCommandType::Builtin::PIN,                            "pin"s },
    { BrewCommandType::Builtin::POSTINSTALL,                    "postinstall"s },
    { BrewCommandType::Builtin::READALL,                        "readall"s },
    { BrewCommandType::Builtin::REINSTALL,                      "reinstall"s },
    { BrewCommandType::Builtin::SEARCH,                         "search"s },
    { BrewCommandType::Builtin::SHELLENV,                       "shellenv"s },
    { BrewCommandType::Builtin::TAP,                            "tap"s },
    { BrewCommandType::Builtin::TAP_INFO,                       "tap-info"s },
    { BrewCommandType::Builtin::UNINSTALL,                      "uninstall"s },
    { BrewCommandType::Builtin::UNLINK,                         "unlink"s },
    { BrewCommandType::Builtin::UNPIN,                          "unpin"s },
    { BrewCommandType::Builtin::UNTAP,                          "untap"s },
    { BrewCommandType::Builtin::UPDATE,                         "update"s },
    { BrewCommandType::Builtin::UPDATE_REPORT,                  "update-report"s },
    { BrewCommandType::Builtin::UPDATE_RESET,                   "update-reset"s },
    { BrewCommandType::Builtin::UPGRADE,                        "upgrade"s },
    { BrewCommandType::Builtin::USES,                           "uses"s },
    { BrewCommandType::Builtin::VENDOR_INSTALL,                 "vendor-install"s },
};

/*! \brief Mapping of built-in developer commands to their respective command heads.
 *         \sa BrewCommandType::BuiltinDev, BrewCommandHead
 */
std::unordered_map<BrewCommandType::BuiltinDev, std::string> const BrewCommandHead::BuiltinDev {
    { BrewCommandType::BuiltinDev::AUDIT,                       "audit"s },
    { BrewCommandType::BuiltinDev::BOTTLE,                      "bottle"s },
    { BrewCommandType::BuiltinDev::BUMP,                        "bump"s },
    { BrewCommandType::BuiltinDev::BUMP_CASK_PR,                "bump-cask-pr"s },
    { BrewCommandType::BuiltinDev::BUMP_FORMULA_PR,             "bump-formula-pr"s },
    { BrewCommandType::BuiltinDev::BUMP_REVISION,               "bump-revision"s },
    { BrewCommandType::BuiltinDev::BUMP_UNVERSIONED_CASKS,      "bump-unversioned-casks"s },
    { BrewCommandType::BuiltinDev::CAT,                         "cat"s },
    { BrewCommandType::BuiltinDev::COMMAND,                     "command"s },
    { BrewCommandType::BuiltinDev::CREATE,                      "create"s },
    { BrewCommandType::BuiltinDev::DISPATCH_BUILD_BOTTLE,       "dispatch-build-bottle"s },
    { BrewCommandType::BuiltinDev::EDIT,                        "edit"s },
    { BrewCommandType::BuiltinDev::EXTRACT,                     "extract"s },
    { BrewCommandType::BuiltinDev::FORMULA,                     "formula"s },
    { BrewCommandType::BuiltinDev::GENERATE_MAN_COMPLETIONS,    "generate-man-completions"s },
    { BrewCommandType::BuiltinDev::INSTALL_BUNDLER_GEMS,        "install-bundler-gems"s },
    { BrewCommandType::BuiltinDev::IRB,                         "irb"s },
    { BrewCommandType::BuiltinDev::LINKAGE,                     "linkage"s },
    { BrewCommandType::BuiltinDev::LIVECHECK,                   "livecheck"s },
    { BrewCommandType::BuiltinDev::PR_AUTOMERGE,                "pr-automerge"s },
    { BrewCommandType::BuiltinDev::PR_PUBLISH,                  "pr-publish"s },
    { BrewCommandType::BuiltinDev::PR_PULL,                     "pr-pull"s },
    { BrewCommandType::BuiltinDev::PR_UPLOAD,                   "pr-upload"s },
    { BrewCommandType::BuiltinDev::PROF,                        "prof"s },
    { BrewCommandType::BuiltinDev::RELEASE,                     "release"s },
    { BrewCommandType::BuiltinDev::RUBOCOP,                     "rubocop"s },
    { BrewCommandType::BuiltinDev::RUBY,                        "ruby"s },
    { BrewCommandType::BuiltinDev::SH,                          "sh"s },
    { BrewCommandType::BuiltinDev::SPONSORS,                    "sponsors"s },
    { BrewCommandType::BuiltinDev::STYLE,                       "style"s },
    { BrewCommandType::BuiltinDev::TAP_NEW,                     "tap-new"s },
    { BrewCommandType::BuiltinDev::TEST,                        "test"s },
    { BrewCommandType::BuiltinDev::TESTS,                       "tests"s },
    { BrewCommandType::BuiltinDev::TYPECHECK,                   "typecheck"s },
    { BrewCommandType::BuiltinDev::UNBOTTLED,                   "unbottled"s },
    { BrewCommandType::BuiltinDev::UNPACK,                      "unpack"s },
    { BrewCommandType::BuiltinDev::UPDATE_LICENSE_DATA,         "update-license-data"s },
    { BrewCommandType::BuiltinDev::UPDATE_MAINTAINERS,          "update-maintainers"s },
    { BrewCommandType::BuiltinDev::UPDATE_PYTHON_RESOURCES,     "update-python-resources"s },
    { BrewCommandType::BuiltinDev::UPDATE_TEST,                 "update-test"s },
    { BrewCommandType::BuiltinDev::VENDOR_GEMS,                 "vendor-gems"s },
};

/*! \brief Mapping of external commands to their respective command heads.
 *         \sa BrewCommandType::External, BrewCommandHead
 */
std::unordered_map<BrewCommandType::External, std::string> const BrewCommandHead::External {
    { BrewCommandType::External::ASPELL_DICTIONARIES,           "aspell-dictionaries"s },
    { BrewCommandType::External::DETERMINE_REBOTTLE_RUNNERS,    "determine-rebottle-runners"s },
    { BrewCommandType::External::POSTGRESQL_UPGRADE_DATABASE,   "postgresql-upgrade-database"s },
};

// clang-format on

template <typename T>
inline auto getCommandHead(T key) {
}

template <>
inline auto getCommandHead<BrewCommandType::Builtin>(BrewCommandType::Builtin key) {
    return BrewCommandHead::Builtin.at(key);
}

template <>
inline auto getCommandHead<BrewCommandType::BuiltinDev>(BrewCommandType::BuiltinDev key) {
    return BrewCommandHead::BuiltinDev.at(key);
}

template <>
inline auto getCommandHead<BrewCommandType::External>(BrewCommandType::External key) {
    return BrewCommandHead::External.at(key);
}

#endif
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <concepts>

#include <helpers.h>

std::string const OPT_PREFIX { "--" };

template<typename E>
concept EnumType = std::is_enum_v<E>;

namespace BrewCommandType {
    enum class Builtin;
    enum class BuiltinDev;
    enum class External;
};

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

enum class BrewCommandType::External {
    ASPELL_DICTIONARIES = 0x1,
    DETERMINE_REBOTTLE_RUNNERS,
    POSTGRESQL_UPGRADE_DATABASE,
};

struct BrewCommandHead {
    static std::map<BrewCommandType::Builtin, std::string> const Builtin;
    static std::map<BrewCommandType::BuiltinDev, std::string> const BuiltinDev;
    static std::map<BrewCommandType::External, std::string> const External;
};

std::map<BrewCommandType::Builtin, std::string> const BrewCommandHead::Builtin {
    { BrewCommandType::Builtin::CACHE,                          "--cache" },
    { BrewCommandType::Builtin::CASKROOM,                       "--caskroom" },
    { BrewCommandType::Builtin::CELLAR,                         "--cellar" },
    { BrewCommandType::Builtin::ENV,                            "--env" },
    { BrewCommandType::Builtin::PREFIX,                         "--prefix" },
    { BrewCommandType::Builtin::REPOSITORY,                     "--repository" },
    { BrewCommandType::Builtin::VERSION,                        "--version" },
    { BrewCommandType::Builtin::ANALYTICS,                      "analytics" },
    { BrewCommandType::Builtin::AUTOREMOVE,                     "autoremove" },
    { BrewCommandType::Builtin::CASKS,                          "casks" },
    { BrewCommandType::Builtin::CLEANUP,                        "cleanup" },
    { BrewCommandType::Builtin::COMMANDS,                       "commands" },
    { BrewCommandType::Builtin::COMPLETIONS,                    "completions" },
    { BrewCommandType::Builtin::CONFIG,                         "config" },
    { BrewCommandType::Builtin::DEPS,                           "deps" },
    { BrewCommandType::Builtin::DESC,                           "desc" },
    { BrewCommandType::Builtin::DEVELOPER,                      "developer" },
    { BrewCommandType::Builtin::DOCTOR,                         "doctor" },
    { BrewCommandType::Builtin::FETCH,                          "fetch" },
    { BrewCommandType::Builtin::FORMULAE,                       "formulae" },
    { BrewCommandType::Builtin::GIST_LOGS,                      "gist-logs" },
    { BrewCommandType::Builtin::HELP,                           "help" },
    { BrewCommandType::Builtin::HOME,                           "home" },
    { BrewCommandType::Builtin::INFO,                           "info" },
    { BrewCommandType::Builtin::INSTALL,                        "install" },
    { BrewCommandType::Builtin::LEAVES,                         "leaves" },
    { BrewCommandType::Builtin::LINK,                           "link" },
    { BrewCommandType::Builtin::LIST,                           "list" },
    { BrewCommandType::Builtin::LOG,                            "logv" },
    { BrewCommandType::Builtin::MIGRATE,                        "migrate" },
    { BrewCommandType::Builtin::MISSING,                        "missing" },
    { BrewCommandType::Builtin::OPTIONS,                        "options" },
    { BrewCommandType::Builtin::OUTDATED,                       "outdated" },
    { BrewCommandType::Builtin::PIN,                            "pin" },
    { BrewCommandType::Builtin::POSTINSTALL,                    "postinstall" },
    { BrewCommandType::Builtin::READALL,                        "readall" },
    { BrewCommandType::Builtin::REINSTALL,                      "reinstall" },
    { BrewCommandType::Builtin::SEARCH,                         "search" },
    { BrewCommandType::Builtin::SHELLENV,                       "shellenv" },
    { BrewCommandType::Builtin::TAP,                            "tap" },
    { BrewCommandType::Builtin::TAP_INFO,                       "tap-info" },
    { BrewCommandType::Builtin::UNINSTALL,                      "uninstall" },
    { BrewCommandType::Builtin::UNLINK,                         "unlink" },
    { BrewCommandType::Builtin::UNPIN,                          "unpin" },
    { BrewCommandType::Builtin::UNTAP,                          "untap" },
    { BrewCommandType::Builtin::UPDATE,                         "update" },
    { BrewCommandType::Builtin::UPDATE_REPORT,                  "update-report" },
    { BrewCommandType::Builtin::UPDATE_RESET,                   "update-reset" },
    { BrewCommandType::Builtin::UPGRADE,                        "upgrade" },
    { BrewCommandType::Builtin::USES,                           "uses" },
    { BrewCommandType::Builtin::VENDOR_INSTALL,                 "vendor-install" },
};

std::map<BrewCommandType::BuiltinDev, std::string> const BrewCommandHead::BuiltinDev {
    { BrewCommandType::BuiltinDev::AUDIT,                       "audit" },
    { BrewCommandType::BuiltinDev::BOTTLE,                      "bottle" },
    { BrewCommandType::BuiltinDev::BUMP,                        "bump" },
    { BrewCommandType::BuiltinDev::BUMP_CASK_PR,                "bump-cask-pr" },
    { BrewCommandType::BuiltinDev::BUMP_FORMULA_PR,             "bump-formula-pr" },
    { BrewCommandType::BuiltinDev::BUMP_REVISION,               "bump-revision" },
    { BrewCommandType::BuiltinDev::BUMP_UNVERSIONED_CASKS,      "bump-unversioned-casks" },
    { BrewCommandType::BuiltinDev::CAT,                         "cat" },
    { BrewCommandType::BuiltinDev::COMMAND,                     "command" },
    { BrewCommandType::BuiltinDev::CREATE,                      "create" },
    { BrewCommandType::BuiltinDev::DISPATCH_BUILD_BOTTLE,       "dispatch-build-bottle" },
    { BrewCommandType::BuiltinDev::EDIT,                        "edit" },
    { BrewCommandType::BuiltinDev::EXTRACT,                     "extract" },
    { BrewCommandType::BuiltinDev::FORMULA,                     "formula" },
    { BrewCommandType::BuiltinDev::GENERATE_MAN_COMPLETIONS,    "generate-man-completions" },
    { BrewCommandType::BuiltinDev::INSTALL_BUNDLER_GEMS,        "install-bundler-gems" },
    { BrewCommandType::BuiltinDev::IRB,                         "irb" },
    { BrewCommandType::BuiltinDev::LINKAGE,                     "linkage" },
    { BrewCommandType::BuiltinDev::LIVECHECK,                   "livecheck" },
    { BrewCommandType::BuiltinDev::PR_AUTOMERGE,                "pr-automerge" },
    { BrewCommandType::BuiltinDev::PR_PUBLISH,                  "pr-publish" },
    { BrewCommandType::BuiltinDev::PR_PULL,                     "pr-pull" },
    { BrewCommandType::BuiltinDev::PR_UPLOAD,                   "pr-upload" },
    { BrewCommandType::BuiltinDev::PROF,                        "prof" },
    { BrewCommandType::BuiltinDev::RELEASE,                     "release" },
    { BrewCommandType::BuiltinDev::RUBOCOP,                     "rubocop" },
    { BrewCommandType::BuiltinDev::RUBY,                        "ruby" },
    { BrewCommandType::BuiltinDev::SH,                          "sh" },
    { BrewCommandType::BuiltinDev::SPONSORS,                    "sponsors" },
    { BrewCommandType::BuiltinDev::STYLE,                       "style" },
    { BrewCommandType::BuiltinDev::TAP_NEW,                     "tap-new" },
    { BrewCommandType::BuiltinDev::TEST,                        "test" },
    { BrewCommandType::BuiltinDev::TESTS,                       "tests" },
    { BrewCommandType::BuiltinDev::TYPECHECK,                   "typecheck" },
    { BrewCommandType::BuiltinDev::UNBOTTLED,                   "unbottled" },
    { BrewCommandType::BuiltinDev::UNPACK,                      "unpack" },
    { BrewCommandType::BuiltinDev::UPDATE_LICENSE_DATA,         "update-license-data" },
    { BrewCommandType::BuiltinDev::UPDATE_MAINTAINERS,          "update-maintainers" },
    { BrewCommandType::BuiltinDev::UPDATE_PYTHON_RESOURCES,     "update-python-resources" },
    { BrewCommandType::BuiltinDev::UPDATE_TEST,                 "update-test" },
    { BrewCommandType::BuiltinDev::VENDOR_GEMS,                 "vendor-gems" },
};

std::map<BrewCommandType::External, std::string> const BrewCommandHead::External {
    { BrewCommandType::External::ASPELL_DICTIONARIES,           "aspell-dictionaries" },
    { BrewCommandType::External::DETERMINE_REBOTTLE_RUNNERS,    "determine-rebottle-runners" },
    { BrewCommandType::External::POSTGRESQL_UPGRADE_DATABASE,   "postgresql-upgrade-database" },
};

template <EnumType E, typename ...Args>
class BrewCommand {
private:
public:
};


#endif
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <cstdint>
#include <iostream>
#include <queue>
#include <string>

enum class BrewCommandType : uint8_t {
    Builtin,
    BuiltinDev,
    External
};

enum class BrewCommand : uint8_t {
    HELP = 0x1,
    VERSION = 0x2
};

struct BuiltinInfo {
    // BrewCommand id;
    // std::string name;
    bool is_opt_like;
};

struct BuiltinDevInfo {
    // BrewCommand id;
    // std::string name;
    bool is_opt_like;
};

struct ExternalInfo {
    // BrewCommand id;
    // std::string name;
    bool is_opt_like;
};

class Command {
private:
    BrewCommandType type_;
    BrewCommand cmd_;
    union {
        BuiltinInfo bi_;
        BuiltinDevInfo bdi_;
        ExternalInfo ei_;
    };

public:
    Command()
        : type_(BrewCommandType ::Builtin)
        , cmd_(BrewCommand::HELP)
    {
        switch (type_) {
        case BrewCommandType::Builtin:
            bi_ = { false };
            execute(cmd_);
            break;
        case BrewCommandType::BuiltinDev:
            bdi_ = { false };
            break;
        case BrewCommandType::External:
            ei_ = { false };
            break;
        default:
            break;
        }
    }

    void execute(BrewCommand);
};

void Command::execute(BrewCommand cmd)
{
    std::cout << "ID: " << static_cast<std::underlying_type<BrewCommand>::type>(cmd) << std::endl;
}

#endif
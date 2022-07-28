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

#ifndef PROC_H__
#define PROC_H__

#include <array>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std::string_literals;

inline extern std::size_t const READ_BUFFER_SZ{1024};

inline extern std::string const STDOUT_CAPTURE{"2>/dev/null"s};
inline extern std::string const STDERR_CAPTURE{"2>&1 1>/dev/null"s};
inline extern std::string const STDOUT_STDERR_CAPTURE{"2>&1"s};

inline extern std::string const LE_SPACER{" "s};

namespace BarrelCmd {

enum class Stream {
    STDOUT,
    STDERR,
    STDOUT_STDERR,
};

class Proc {
private:
    std::string const cmd_;
    Stream stream_;

    std::string stream_dump_{};
    int exit_status_{EXIT_SUCCESS};

public:
    explicit Proc(std::string const&);
    explicit Proc(std::string const&, Stream);

public:
    std::string const& getStreamDump() const;
    int getExitCode() const;

public:
    void execute();
};

Proc::Proc(std::string const& cmd, Stream stream) : cmd_(cmd), stream_(stream){};

Proc::Proc(std::string const& cmd) : Proc{cmd, Stream::STDOUT} {};

std::string const& Proc::getStreamDump() const {
    return stream_dump_;
}

int Proc::getExitCode() const {
    return WEXITSTATUS(exit_status_);
}

void Proc::execute() {
    const char* MODE = "r";
    std::array<char, READ_BUFFER_SZ> read_buffer;

    std::string capture;

    switch (stream_) {
    case Stream::STDOUT:
        capture = STDOUT_CAPTURE;
        break;
    case Stream::STDERR:
        capture = STDERR_CAPTURE;
        break;
    case Stream::STDOUT_STDERR:
        capture = STDOUT_STDERR_CAPTURE;
        break;
    default:
        break;
    }

    std::string const cmd = cmd_ + LE_SPACER + capture;

    auto fptr_del = [&exit_status_ = exit_status_](FILE* file) { exit_status_ = pclose(file); };
    std::unique_ptr<FILE, decltype(fptr_del)> file(popen(cmd.c_str(), MODE), fptr_del);

    if (file == nullptr) {
        throw std::runtime_error("Proc::execute(): popen() failed to initialize");
    }

    std::size_t read_bytes;
    while ((read_bytes = std::fread(read_buffer.data(), sizeof(read_buffer.at(0)), sizeof(read_buffer),
                                    file.get())) != 0) {
        stream_dump_ += std::string(read_buffer.data(), read_bytes);
    }
}

} // namespace BarrelCmd

#endif
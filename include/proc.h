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

inline extern std::size_t const READ_BUFFER_SZ{1024};

class SpawnProc {
private:
    std::string const cmd_;

    std::string stdout_dump_{};
    std::string stderr_dump_{};
    int exit_status_{EXIT_SUCCESS};

public:
    explicit SpawnProc(std::string const&);

public:
    std::string const& getStdoutDump() const;
    std::string const& getStderrDump() const;
    int getExitCode() const;

public:
    void readStreamData();
};

SpawnProc::SpawnProc(std::string const& cmd) : cmd_(cmd){};

std::string const& SpawnProc::getStdoutDump() const {
    return stdout_dump_;
}

std::string const& SpawnProc::getStderrDump() const {
    return stderr_dump_;
}

int SpawnProc::getExitCode() const {
    return WEXITSTATUS(exit_status_);
}

void SpawnProc::readStreamData() {
    const char* MODE = "r";
    std::array<char, READ_BUFFER_SZ> read_buffer;

    auto fptr_del = [&exit_status_ = exit_status_](FILE* file) { exit_status_ = pclose(file); };
    std::unique_ptr<FILE, decltype(fptr_del)> file(popen(cmd_.c_str(), MODE), fptr_del);

    if (file == nullptr) {
        throw std::runtime_error("SpawnProc::readStreamData(): popen() failed to initialize");
    }

    std::size_t read_bytes;
    while ((read_bytes = std::fread(read_buffer.data(), sizeof(read_buffer.at(0)), sizeof(read_buffer),
                                    file.get())) != 0) {
        stdout_dump_ += std::string(read_buffer.data(), read_bytes);
    }
}

#endif
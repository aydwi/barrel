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

#ifndef SPEC_H__
#define SPEC_H__

#include <string>

using namespace std::string_literals;

namespace BrewSpec {
inline extern std::string const _BREW_DEFAULT_ALIAS{"brew"s};
inline extern std::string const _BREW_DEFAULT_PATH_X86_64{"/usr/local/bin/brew"s};
inline extern std::string const _BREW_DEFAULT_PATH_ARM64{"/opt/homebrew/bin/brew"s};
} // namespace BrewSpec

namespace BarrelSpec {
inline extern std::string const _BREW_VERSION{"Homebrew 3.5.4"s};
} // namespace BarrelSpec

#endif
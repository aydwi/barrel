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

#ifndef UTILS_H__
#define UTILS_H__

#include <concepts>
#include <type_traits>

template <typename E>
concept EnumType = std::is_enum_v<E>;

//
// Get the integral "underlying type" of an "enumerator" from a scoped enumeration
//
template <EnumType E>
constexpr auto enumUnderlyingType(E const enumerator) {
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

#endif
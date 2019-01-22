/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "CapsLockStatusChecker.h"

namespace kImageAnnotator {

bool CapsLockStatusChecker::isCapsLockEnabled()
{
#if defined(_WIN32)
    return GetKeyState(VK_CAPITAL) == 1;
#elif defined(_UNIX)
    auto display = XOpenDisplay((char*)0);
    auto capsState = false;
    if (display) {
        unsigned n;
        XkbGetIndicatorState(display, XkbUseCoreKbd, &n);
        capsState = (n & 0x01) == 1;
    }
    return capsState;
#else
    return false;
#endif
}

} // namespace kImageAnnotator
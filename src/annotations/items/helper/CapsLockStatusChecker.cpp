/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

/*
 * Currently we need to keep the x11 include in the definition
 * file as x11 and qt::cursor don't work together and we fail
 * to compile
 */

#if defined(__linux__)

#include <X11/Xlib.h>
#include <X11/XKBlib.h>

#endif

namespace kImageAnnotator {

bool CapsLockStatusChecker::isCapsLockEnabled()
{
#if defined(_WIN32)
	return GetKeyState(VK_CAPITAL) == 1;
#elif defined(__linux__)
	auto display = XOpenDisplay(nullptr);
	auto capsState = false;
	if (display) {
		unsigned n;
		XkbGetIndicatorState(display, XkbUseCoreKbd, &n);
		capsState = (n & 0x01) == 1;
	}
	XCloseDisplay(display);
	return capsState;
#else
	return false;
#endif
}

} // namespace kImageAnnotator
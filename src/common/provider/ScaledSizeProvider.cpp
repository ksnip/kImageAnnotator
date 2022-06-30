/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "ScaledSizeProvider.h"

namespace kImageAnnotator {

int ScaledSizeProvider::scaledWidth(int width)
{
	return (int)(width * scaleFactor());
}

QSize ScaledSizeProvider::scaledSize(const QSize &size)
{
	return size * scaleFactor();
}

QSize ScaledSizeProvider::toolButtonIconSize()
{
	return scaledSize(Constants::ToolButtonIconSize);
}

QSize ScaledSizeProvider::settingsWidgetSize()
{
	return scaledSize(Constants::SettingsWidgetSize);
}

QSize ScaledSizeProvider::settingsWidgetIconSize()
{
	return scaledSize(Constants::SettingsWidgetIconSize);
}

QSize ScaledSizeProvider::menuItemIconSize()
{
	return scaledSize(Constants::MenuItemIconSize);
}

int ScaledSizeProvider::resizeHandleSize()
{
	return scaledWidth(Constants::ResizeHandleSize);
}

qreal ScaledSizeProvider::scaleFactor()
{
	static auto scaleFactor = getScaleFactor();
	return scaleFactor;
}

qreal ScaledSizeProvider::getScaleFactor()
{
#if defined(__linux__)
	char env = getLinuxDesktopEnvironment();
	if (env == 'g') {
		auto screen = QApplication::primaryScreen();
		auto logicalDotsPerInch = (int) screen->logicalDotsPerInch();
		auto physicalDotsPerInch = (int) screen->physicalDotsPerInch();
		return (qreal)logicalDotsPerInch / (qreal)physicalDotsPerInch;
	} else if (env == 'k') {
		auto screen = QApplication::primaryScreen();
		return screen->devicePixelRatio();
	}
#endif

	return 1;
}

#if defined(__linux__)
char ScaledSizeProvider::getLinuxDesktopEnvironment()
{
	auto currentDesktop = QString(qgetenv("XDG_CURRENT_DESKTOP"));
	if (currentDesktop.contains(QLatin1String("gnome"), Qt::CaseInsensitive)
		|| currentDesktop.contains(QLatin1String("unity"), Qt::CaseInsensitive)) {
		return 'g';
	} else if (currentDesktop.contains(QLatin1String("kde"), Qt::CaseInsensitive)) {
		return 'k';
	} else {
		return ' ';
	}
}
#endif

} // namespace kImageAnnotator

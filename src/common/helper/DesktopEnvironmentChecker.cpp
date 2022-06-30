/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#include "DesktopEnvironmentChecker.h"

namespace kImageAnnotator {
    
DesktopEnvironmentType DesktopEnvironmentChecker::getDesktopEnvironment() 
{
    auto currentDesktop = QString(qgetenv("XDG_CURRENT_DESKTOP"));

    if (contains(currentDesktop, QLatin1String("gnome")) || contains(currentDesktop, QLatin1String("unity"))) {
        return DesktopEnvironmentType::Gnome;
    } else if (contains(currentDesktop, QLatin1String("kde"))) {
        return DesktopEnvironmentType::Kde;
    } else {
        return DesktopEnvironmentType::Unknown;
    }
}

bool DesktopEnvironmentChecker::contains(const QString &value1, const QLatin1String &value2)
{ 
    return value1.contains(value2, Qt::CaseInsensitive);
}

} // namespace kImageAnnotator
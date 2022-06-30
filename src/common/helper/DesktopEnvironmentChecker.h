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

#ifndef KIMAGEANNOTATOR_DESKTOPENVIRONMENTCHECKER_H
#define KIMAGEANNOTATOR_DESKTOPENVIRONMENTCHECKER_H

#include <QApplication>

#include "src/common/enum/DesktopEnvironmentType.h"

namespace kImageAnnotator {

class DesktopEnvironmentChecker
{
public:
    DesktopEnvironmentChecker() = default;
    ~DesktopEnvironmentChecker() = default;

    DesktopEnvironmentType getDesktopEnvironment();

    static bool contains(const QString &value1, const QLatin1String &value2) ;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_DESKTOPENVIRONMENTCHECKER_H

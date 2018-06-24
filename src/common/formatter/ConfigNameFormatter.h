/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H
#define KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H

#include <QString>

#include "../enum/ToolTypes.h"

class ConfigNameFormatter
{
public:
    static QString annotationTool(ToolTypes tool);
    static QString toolOutlineColor(ToolTypes tool);
    static QString toolFillColor(ToolTypes tool);
    static QString toolForegroundColor(ToolTypes tool);
    static QString toolSize(ToolTypes tool);
    static QString toolFillType(ToolTypes tool);

private:
    explicit ConfigNameFormatter() = default;
};

#endif // KIMAGEANNOTATOR_CONFIGNAMEFORMATTER_H

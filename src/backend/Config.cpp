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

#include "Config.h"

Config* Config::instance()
{
    static Config instance;
    return &instance;
}

QPointF Config::windowPosition() const
{
    return mConfig.value(QStringLiteral("Application/WindowPosition"), QPointF(200, 200)).value<QPointF>();
}

void Config::setWindowPosition(const QPointF& position)
{
    if(windowPosition() == position) {
        return;
    }

    mConfig.setValue(QStringLiteral("Application/WindowPosition"), position);
    mConfig.sync();
}

ToolTypes Config::selectedTool() const
{
    return mConfig.value(QStringLiteral("Application/SelectedTool"), static_cast<int>(ToolTypes::Arrow)).value<ToolTypes>();
}

void Config::setSelectedTool(ToolTypes tool)
{
    if(selectedTool() == tool) {
        return;
    }

    mConfig.setValue(QStringLiteral("Application/SelectedTool"), static_cast<int>(tool));
    mConfig.sync();
}

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

QColor Config::toolColor(ToolTypes tool)
{
    return mConfig.value(createToolColorString(tool), QColor(Qt::red)).value<QColor>();
}

void Config::setToolColor(const QColor& color, ToolTypes tool)
{
    if(toolColor(tool) == color) {
        return;
    }

    mConfig.setValue(createToolColorString(tool), color);
    mConfig.sync();
}

Config::Config()
{
    // You must set the application name via QCoreApplication::setApplicationName before using the configuration
    if(mConfig.status() == QSettings::AccessError) {
        qCritical("Configuration error! Are you trying to read configuration before settings Application Name?");
    }
};

QString Config::createToolColorString(ToolTypes tool) const
{
    return ConfigNameFormatter::toolColorString(tool);
}

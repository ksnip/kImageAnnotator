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

#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>
#include <QPointF>
#include <QColor>

#include "../common/enum/ToolTypes.h"
#include "../common/enum/FillTypes.h"
#include "../common/formatter/ConfigNameFormatter.h"

class Config : public QObject
{
    Q_OBJECT

public slots:
    static Config *instance();

    ToolTypes selectedTool() const;
    void setSelectedTool(ToolTypes tool);

    QColor toolOutlineColor(ToolTypes tool) const;
    void setToolOutlineColor(const QColor& color, ToolTypes tool);

    QColor toolFillColor(ToolTypes tool) const;
    void setToolFillColor(const QColor& color, ToolTypes tool);

    QColor toolForegroundColor(ToolTypes tool) const;
    void setToolForegroundColor(const QColor& color, ToolTypes tool);

    int toolSize(ToolTypes tool) const;
    void setToolSize(int size, ToolTypes tool);

    FillTypes toolFillType(ToolTypes tool) const;
    void setToolFillType(FillTypes fillType, ToolTypes tool);

private:
    QSettings mConfig;

    explicit Config();
};

#endif // CONFIG_H

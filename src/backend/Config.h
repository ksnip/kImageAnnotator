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

#ifndef KIMAGEANNOTATOR_CONFIG_H
#define KIMAGEANNOTATOR_CONFIG_H

#include <QObject>
#include <QPointF>
#include <QColor>
#include <QHash>

#include "src/common/enum/ToolTypes.h"
#include "src/common/enum/FillTypes.h"

class Config : public QObject
{
    Q_OBJECT

public slots:
    static Config *instance();

    ToolTypes selectedTool() const;
    void setSelectedTool(ToolTypes tool);

    QColor toolColor(ToolTypes tool) const;
    void setToolColor(const QColor& color, ToolTypes tool);

    QColor toolTextColor(ToolTypes tool) const;
    void setToolForegroundColor(const QColor& color, ToolTypes tool);

    int toolSize(ToolTypes tool) const;
    void setToolSize(int size, ToolTypes tool);

    FillTypes toolFillType(ToolTypes tool) const;
    void setToolFillType(FillTypes fillType, ToolTypes tool);

signals:
    void toolChanged(ToolTypes tool) const;

private:
    ToolTypes mSelectTool;
    QHash<ToolTypes, QColor> mToolToColor;
    QHash<ToolTypes, QColor> mToolToTextColor;
    QHash<ToolTypes, int> mToolToSize;
    QHash<ToolTypes, FillTypes> mToolToFillType;

    explicit Config();
    void initSelectedTool();
    void initDefaultToolColors();
    void initDefaultTextColors();
    void initDefaultSizes();
    void initDefaultFillTypes();
};

#endif // KIMAGEANNOTATOR_CONFIG_H

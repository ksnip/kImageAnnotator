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

namespace kImageAnnotator {

Config *Config::instance()
{
    static Config instance;
    return &instance;
}

ToolTypes Config::selectedTool() const
{
    return mSelectTool;
}

void Config::setSelectedTool(ToolTypes tool)
{
    if (selectedTool() == tool) {
        return;
    }

    mSelectTool = tool;
    emit toolChanged(tool);
}

QColor Config::toolColor(ToolTypes tool) const
{
    return mToolToColor[tool];
}

void Config::setToolColor(const QColor &color, ToolTypes tool)
{
    if (toolColor(tool) == color) {
        return;
    }

    mToolToColor[tool] = color;
}

QColor Config::toolTextColor(ToolTypes tool) const
{
    return mToolToTextColor[tool];
}

void Config::setToolTextColor(const QColor &color, ToolTypes tool)
{
    if (toolTextColor(tool) == color) {
        return;
    }

    mToolToTextColor[tool] = color;
}

int Config::toolSize(ToolTypes tool) const
{
    return mToolToSize[tool];
}

void Config::setToolSize(int size, ToolTypes tool)
{
    if (toolSize(tool) == size) {
        return;
    }

    mToolToSize[tool] = size;
}

FillTypes Config::toolFillType(ToolTypes tool) const
{
    return mToolToFillType[tool];
}

void Config::setToolFillType(FillTypes fillType, ToolTypes tool)
{
    if (toolFillType(tool) == fillType) {
        return;
    }

    mToolToFillType[tool] = fillType;
}

// Private Methodes

Config::Config()
{
    initSelectedTool();
    initDefaultToolColors();
    initDefaultTextColors();
    initDefaultSizes();
    initDefaultFillTypes();
}

void Config::initSelectedTool()
{
    mSelectTool = ToolTypes::Pen;
};

void Config::initDefaultToolColors()
{
    mToolToColor[ToolTypes::Pen] = QColor(Qt::red);
    mToolToColor[ToolTypes::Marker] = QColor(Qt::yellow);
    mToolToColor[ToolTypes::Line] = QColor(Qt::blue);
    mToolToColor[ToolTypes::Arrow] = QColor(Qt::red);
    mToolToColor[ToolTypes::Rect] = QColor(Qt::green);
    mToolToColor[ToolTypes::Ellipse] = QColor(Qt::gray);
    mToolToColor[ToolTypes::Number] = QColor(Qt::red);
    mToolToColor[ToolTypes::Text] = QColor(Qt::black);
}

void Config::initDefaultTextColors()
{
    mToolToTextColor[ToolTypes::Number] = QColor(Qt::white);
    mToolToTextColor[ToolTypes::Text] = QColor(Qt::white);
}

void Config::initDefaultSizes()
{
    mToolToSize[ToolTypes::Pen] = 3;
    mToolToSize[ToolTypes::Marker] = 10;
    mToolToSize[ToolTypes::Line] = 3;
    mToolToSize[ToolTypes::Arrow] = 6;
    mToolToSize[ToolTypes::Rect] = 3;
    mToolToSize[ToolTypes::Ellipse] = 3;
    mToolToSize[ToolTypes::Number] = 5;
    mToolToSize[ToolTypes::Text] = 10;
}

void Config::initDefaultFillTypes()
{
    mToolToFillType[ToolTypes::Pen] = FillTypes::NoFill;
    mToolToFillType[ToolTypes::Marker] = FillTypes::NoFill;
    mToolToFillType[ToolTypes::Line] = FillTypes::NoFill;
    mToolToFillType[ToolTypes::Arrow] = FillTypes::Fill;
    mToolToFillType[ToolTypes::Rect] = FillTypes::NoFill;
    mToolToFillType[ToolTypes::Ellipse] = FillTypes::NoFill;
    mToolToFillType[ToolTypes::Number] = FillTypes::Fill;
    mToolToFillType[ToolTypes::Text] = FillTypes::NoFill;
}

} // namespace kImageAnnotator

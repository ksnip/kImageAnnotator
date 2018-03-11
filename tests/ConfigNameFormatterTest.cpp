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

#include "ConfigNameFormatterTest.h"

void ConfigNameFormatterTest::initTestCase()
{
    toolList.append(ToolTypes::Arrow);
    toolList.append(ToolTypes::Line);
    toolList.append(ToolTypes::Ellipse);
    toolList.append(ToolTypes::Number);
    toolList.append(ToolTypes::Rect);
    toolList.append(ToolTypes::Select);
}

void ConfigNameFormatterTest::TestToolString_Should_FormatToolStringCorrectly()
{
    for(auto tool : toolList) {
        auto result = ConfigNameFormatter::annotationTool(tool);

        auto expected = QStringLiteral("AnnotationTool_") + QString::number(static_cast<int>(tool));
        QCOMPARE(result, expected);
    }
}

void ConfigNameFormatterTest::TestToolColorString_Should_FormatToolStringCorrectly()
{
    for(auto tool : toolList) {
        auto result = ConfigNameFormatter::toolOutlineColor(tool);

        auto expected = QStringLiteral("Application/AnnotationTool_") + QString::number(static_cast<int>(tool)) + QStringLiteral("_OutlineColor");
        QCOMPARE(result, expected);
    }
}

void ConfigNameFormatterTest::TestToolSizeString_Should_FormatToolStringCorrectly()
{
    for(auto tool : toolList) {
        auto result = ConfigNameFormatter::toolSize(tool);

        auto expected = QStringLiteral("Application/AnnotationTool_") + QString::number(static_cast<int>(tool)) + QStringLiteral("_Size");
        QCOMPARE(result, expected);
    }
}

void ConfigNameFormatterTest::TestToolFillTypeString_Should_FormatToolStringCorrectly()
{
    for(auto tool : toolList) {
        auto result = ConfigNameFormatter::toolFillType(tool);

        auto expected = QStringLiteral("Application/AnnotationTool_") + QString::number(static_cast<int>(tool)) + QStringLiteral("_FillType");
        QCOMPARE(result, expected);
    }
}


QTEST_MAIN(ConfigNameFormatterTest);

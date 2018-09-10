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

#include "AnnotationPropertiesFactoryTest.h"

void AnnotationPropertiesFactoryTest::initTestCase()
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("/tmp"));
}

void AnnotationPropertiesFactoryTest::cleanupTestCase()
{
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("$HOME/.config"));
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesSizeBasedOnConfiguration()
{
    const int size = 13;
    const ToolTypes tool = ToolTypes::Line;
    auto configInstance = Config::instance();
    configInstance->setToolSize(size, tool);
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.size(), size);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesColorBasedOnConfiguration()
{
    const QColor color(Qt::darkMagenta);
    const ToolTypes tool = ToolTypes::Line;
    auto configInstance = Config::instance();
    configInstance->setToolColor(color, tool);
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.color(), color);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesForegroundColorBasedOnConfiguration()
{
    const QColor foregroundColor(Qt::darkMagenta);
    const ToolTypes tool = ToolTypes::Number;
    auto configInstance = Config::instance();
    configInstance->setToolForegroundColor(foregroundColor, tool);
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.textColor(), foregroundColor);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesFillBasedOnConfiguration()
{
    const FillTypes fill = FillTypes::NoFill;
    const ToolTypes tool = ToolTypes::Rect;
    auto configInstance = Config::instance();
    configInstance->setToolFillType(fill, tool);
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.fillType(), fill);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetShadowEnabledToFalse_When_ToolIsMarker()
{
    const ToolTypes tool = ToolTypes::Marker;
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.shadowEnabled(), false);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetShadowEnabledToTrue_When_ToolIsNotMarker()
{
    QFETCH(ToolTypes, testTool);
    const ToolTypes tool = testTool;
    AnnotationPropertiesFactory propertiesFactory;

    auto properties = propertiesFactory.createProperties(tool);

    QCOMPARE(properties.shadowEnabled(), true);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetShadowEnabledToTrue_When_ToolIsNotMarker_data()
{
    QTest::addColumn<ToolTypes>("testTool");

    QTest::newRow("set1") << ToolTypes::Pen;
    QTest::newRow("set2") << ToolTypes::Number;
    QTest::newRow("set3") << ToolTypes::Arrow;
    QTest::newRow("set4") << ToolTypes::Line;
    QTest::newRow("set5") << ToolTypes::Ellipse;
    QTest::newRow("set6") << ToolTypes::Rect;
}

QTEST_MAIN(AnnotationPropertiesFactoryTest);

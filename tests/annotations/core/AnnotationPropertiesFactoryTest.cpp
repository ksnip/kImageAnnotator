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

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesSizeBasedOnConfiguration()
{
	const int size = 13;
	const ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	config->setToolWidth(size, tool);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->Width(), size);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesColorBasedOnConfiguration()
{
	const QColor color(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	config->setToolColor(color, tool);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->color(), color);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesTextColorBasedOnConfiguration()
{
	const QColor foregroundColor(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Number;
	auto config = new Config;
	config->setToolTextColor(foregroundColor, tool);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->textColor(), foregroundColor);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesFillTypeBasedOnConfiguration()
{
	const FillTypes fill = FillTypes::NoFill;
	const ToolTypes tool = ToolTypes::Rect;
	auto configInstance = new Config;
	configInstance->setToolFillType(fill, tool);
	AnnotationPropertiesFactory propertiesFactory(configInstance);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->fillType(), fill);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetShadowEnabledBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto config = new Config;
	auto enabled = true;
	config->setItemShadowEnabled(enabled);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->shadowEnabled(), enabled);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreatePathPropertiesWhenItemPen()
{
	const ToolTypes tool = ToolTypes::Pen;
	AnnotationPropertiesFactory propertiesFactory(new Config);
	auto properties = propertiesFactory.create(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreatePathPropertiesWhenItemMarker()
{
	const ToolTypes tool = ToolTypes::Marker;
	AnnotationPropertiesFactory propertiesFactory(new Config);
	auto properties = propertiesFactory.create(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreateTextPropertiesWhenItemNumber()
{
	const ToolTypes tool = ToolTypes::Number;
	AnnotationPropertiesFactory propertiesFactory(new Config);
	auto properties = propertiesFactory.create(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreateTextPropertiesWhenItemText()
{
	const ToolTypes tool = ToolTypes::Text;
	AnnotationPropertiesFactory propertiesFactory(new Config);
	auto properties = propertiesFactory.create(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetSmootPathBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto config = new Config;
	auto smootPathEnabled = true;
	auto smootPathFactor = 99;
	config->setSmoothPathEnabled(smootPathEnabled);
	config->setSmoothFactor(smootPathFactor);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QCOMPARE(pathProperties->smoothPathEnabled(), smootPathEnabled);
	QCOMPARE(pathProperties->smoothFactor(), smootPathFactor);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetToolFontAndFontSizeBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Number;
	auto config = new Config;
	auto font = QFont("Helvetica [Cronyx]", 8, QFont::StyleItalic);
	config->setToolFont(font, tool);
	config->setToolFontSize(8, tool);
	AnnotationPropertiesFactory propertiesFactory(config);

	auto properties = propertiesFactory.create(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QCOMPARE(textProperties->font(), font);
}

QTEST_MAIN(AnnotationPropertiesFactoryTest);

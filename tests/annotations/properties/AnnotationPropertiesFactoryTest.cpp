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

	QCOMPARE(properties->size(), size);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesColorBasedOnConfiguration()
{
	const QColor color(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Line;
	auto configInstance = Config::instance();
	configInstance->setToolColor(color, tool);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	QCOMPARE(properties->color(), color);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesTextColorBasedOnConfiguration()
{
	const QColor foregroundColor(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Number;
	auto configInstance = Config::instance();
	configInstance->setToolTextColor(foregroundColor, tool);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	QCOMPARE(properties->textColor(), foregroundColor);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetPropertiesFillTypeBasedOnConfiguration()
{
	const FillTypes fill = FillTypes::NoFill;
	const ToolTypes tool = ToolTypes::Rect;
	auto configInstance = Config::instance();
	configInstance->setToolFillType(fill, tool);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	QCOMPARE(properties->fillType(), fill);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetShadowEnabledBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto configInstance = Config::instance();
	auto enabled = true;
	configInstance->setItemShadowEnabled(enabled);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	QCOMPARE(properties->shadowEnabled(), enabled);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_CreatePathPropertiesWhenItemPen()
{
	const ToolTypes tool = ToolTypes::Pen;
	AnnotationPropertiesFactory propertiesFactory;
	auto properties = propertiesFactory.createProperties(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_CreatePathPropertiesWhenItemMarker()
{
	const ToolTypes tool = ToolTypes::Marker;
	AnnotationPropertiesFactory propertiesFactory;
	auto properties = propertiesFactory.createProperties(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_CreateTextPropertiesWhenItemNumber()
{
	const ToolTypes tool = ToolTypes::Number;
	AnnotationPropertiesFactory propertiesFactory;
	auto properties = propertiesFactory.createProperties(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_CreateTextPropertiesWhenItemText()
{
	const ToolTypes tool = ToolTypes::Text;
	AnnotationPropertiesFactory propertiesFactory;
	auto properties = propertiesFactory.createProperties(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetSmootPathBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto configInstance = Config::instance();
	auto smootPathEnabled = true;
	auto smootPathFactor = 99;
	configInstance->setSmoothPathEnabled(smootPathEnabled);
	configInstance->setSmoothFactor(smootPathFactor);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	QCOMPARE(pathProperties->smoothPathEnabled(), smootPathEnabled);
	QCOMPARE(pathProperties->smoothFactor(), smootPathFactor);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetNumberFontBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Number;
	auto configInstance = Config::instance();
	auto font = QFont("Helvetica [Cronyx]", 8, QFont::StyleItalic);
	configInstance->setNumberFont(font);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QCOMPARE(textProperties->font(), font);
}

void AnnotationPropertiesFactoryTest::TestCreateProperties_Should_SetTextFontBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Text;
	auto configInstance = Config::instance();
	auto font = QFont("Helvetica [Cronyx]", 12, QFont::StyleItalic);
	configInstance->setTextFont(font);
	AnnotationPropertiesFactory propertiesFactory;

	auto properties = propertiesFactory.createProperties(tool);

	auto textProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	QCOMPARE(textProperties->font(), font);
}

QTEST_MAIN(AnnotationPropertiesFactoryTest);

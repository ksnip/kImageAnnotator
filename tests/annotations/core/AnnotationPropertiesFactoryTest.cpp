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
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolWidth(size);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->width(), size);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesColorBasedOnConfiguration()
{
	const QColor color(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Line;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	settingsProvider->setToolColor(color);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->color(), color);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesTextColorBasedOnConfiguration()
{
	const QColor textColor(Qt::darkMagenta);
	const ToolTypes tool = ToolTypes::Number;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	settingsProvider->setTextColor(textColor);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->textColor(), textColor);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesFillTypeBasedOnConfiguration()
{
	const FillTypes fill = FillTypes::BorderAndNoFill;
	const ToolTypes tool = ToolTypes::Rect;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	settingsProvider->setFillType(fill);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->fillType(), fill);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetShadowEnabledBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto config = new Config;
	auto enabled = true;
	config->setItemShadowEnabled(enabled);
	auto settingsProvider = new MockSettingsProvider();
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->shadowEnabled(), enabled);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreatePathPropertiesWhenItemPen()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	auto properties = propertiesFactory.create(tool);

	auto pathProperties = properties.dynamicCast<AnnotationPathProperties>();

	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreatePathPropertiesWhenItemMarker()
{
	const ToolTypes tool = ToolTypes::MarkerPen;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	auto properties = propertiesFactory.create(tool);

	auto pathProperties = properties.dynamicCast<AnnotationPathProperties>();

	QVERIFY(pathProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreateTextPropertiesWhenItemNumber()
{
	const ToolTypes tool = ToolTypes::Number;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	auto properties = propertiesFactory.create(tool);

	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();

	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreateTextPropertiesWhenItemNumberPointer()
{
	const ToolTypes tool = ToolTypes::NumberPointer;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	auto properties = propertiesFactory.create(tool);

	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();

	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreateTextPropertiesWhenItemText()
{
	const ToolTypes tool = ToolTypes::Text;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	auto properties = propertiesFactory.create(tool);

	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();

	QVERIFY(textProperties != nullptr);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetSmoothPathBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Pen;
	auto config = new Config;
	auto smoothPathEnabled = true;
	auto smoothPathFactor = 99;
	config->setSmoothPathEnabled(smoothPathEnabled);
	config->setSmoothFactor(smoothPathFactor);
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	auto pathProperties = properties.dynamicCast<AnnotationPathProperties>();

	QCOMPARE(pathProperties->smoothPathEnabled(), smoothPathEnabled);
	QCOMPARE(pathProperties->smoothFactor(), smoothPathFactor);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetToolFontAndFontSizeBasedOnConfiguration()
{
	const ToolTypes tool = ToolTypes::Number;
	auto config = new Config;
	auto font = QFont("Helvetica [Cronyx]", 8, QFont::StyleItalic);
	config->setToolFont(font, tool);
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setFontSize(8);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();

	QCOMPARE(textProperties->font(), font);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_StickerPathBasedOnSettings()
{
	const ToolTypes tool = ToolTypes::Sticker;
	auto path = QStringLiteral("/my/path/to/sticker");
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setSticker(path);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	auto stickerProperties = properties.dynamicCast<AnnotationStickerProperties>();
	QCOMPARE(stickerProperties->path(), path);
}

QTEST_MAIN(AnnotationPropertiesFactoryTest);

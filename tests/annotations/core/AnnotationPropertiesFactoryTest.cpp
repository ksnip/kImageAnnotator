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
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QLatin1Literal("/tmp"));
}

void AnnotationPropertiesFactoryTest::cleanupTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QLatin1Literal("$HOME/.config"));
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_SetPropertiesSizeBasedOnConfiguration()
{
	const int size = 13;
	auto tool = Tools::Line;
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
	auto tool = Tools::Line;
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
	auto tool = Tools::Number;
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
	auto fill = FillModes::BorderAndNoFill;
	auto tool = Tools::Rect;
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
	auto tool = Tools::Pen;
	auto config = new Config;
	auto enabled = true;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setShadowEnabled(enabled);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	QCOMPARE(properties->shadowEnabled(), enabled);
}

void AnnotationPropertiesFactoryTest::TestCreate_Should_CreatePathPropertiesWhenItemPen()
{
	auto tool = Tools::Pen;
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
	auto tool = Tools::MarkerPen;
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
	auto tool = Tools::Number;
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
	auto tool = Tools::NumberPointer;
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
	auto tool = Tools::Text;
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
	auto tool = Tools::Pen;
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
	auto tool = Tools::Number;
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
	auto tool = Tools::Sticker;
	auto path = QLatin1Literal("/my/path/to/sticker");
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setSticker(path);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);

	auto properties = propertiesFactory.create(tool);

	auto stickerProperties = properties.dynamicCast<AnnotationStickerProperties>();
	QCOMPARE(stickerProperties->path(), path);
}

QTEST_MAIN(AnnotationPropertiesFactoryTest);

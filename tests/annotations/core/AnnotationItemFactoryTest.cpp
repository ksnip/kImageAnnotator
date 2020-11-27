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

#include "AnnotationItemFactoryTest.h"

void AnnotationItemFactoryTest::initTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("/tmp"));
}

void AnnotationItemFactoryTest::cleanupTestCase()
{
	QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, QStringLiteral("$HOME/.config"));
}

void AnnotationItemFactoryTest::TestCreate_Should_CreateItemAtProvidedPosition()
{
	QPointF position(10, 10);
	auto toolType = Tools::Line;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(toolType);
	settingsProvider->setToolWidth(0);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(position);
	item->addPoint(QPoint(20, 20), false);

	QCOMPARE(item->position(), position);
}

void AnnotationItemFactoryTest::TestCreate_Should_CreateImageItemAtProvidedPosition()
{
	QPointF position(10, 10);
	QPixmap image(200,200);
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Image);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(position, image);

	QVERIFY(dynamic_cast<AnnotationImage*>(item) != nullptr);
	QCOMPARE(item->position(), position);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnNullPtrForUnknownType()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType((Tools) 21);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	QVERIFY(item == nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationLine_When_TypeIsLine()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Line);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationLine *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationArrow_When_TypeIsArrow()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Arrow);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationArrow *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationRect_When_TypeIsRect()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Rect);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationRect *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationEllipse_When_TypeIsEllipse()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Ellipse);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationEllipse *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationNumber_When_TypeIsNumber()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Number);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationNumber *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationSticker_When_TypeIsSticker()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::Sticker);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationSticker *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreate_Should_ReturnAnnotationNumberPointer_When_TypeIsNumberPointer()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(Tools::NumberPointer);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);

	auto item = itemFactory.create(QPoint(0, 0));

	auto result = dynamic_cast<AnnotationNumberPointer *>(item);
	QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestClone_Should_ReturnNewItemOfSameType()
{
	QPointF position(10, 10);
	auto tool = Tools::Line;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);
	auto item = itemFactory.create(position);
	item->addPoint(QPoint(20, 20), false);

	auto clonedItem = itemFactory.clone(item);

	QVERIFY(clonedItem != item);
	QCOMPARE(clonedItem->toolType(), item->toolType());
}

void AnnotationItemFactoryTest::TestClone_Should_IncrementZValueForClonedItem()
{
	QPointF position(10, 10);
	auto tool = Tools::Line;
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	settingsProvider->setToolType(tool);
	AnnotationPropertiesFactory propertiesFactory(config, settingsProvider);
	AnnotationItemFactory itemFactory(&propertiesFactory, settingsProvider);
	auto item = itemFactory.create(position);
	item->addPoint(QPoint(20, 20), false);

	auto clonedItem = itemFactory.clone(item);

	QVERIFY(clonedItem->zValue() > item->zValue());
}

QTEST_MAIN(AnnotationItemFactoryTest);

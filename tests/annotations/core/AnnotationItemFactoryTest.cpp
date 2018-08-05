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

void AnnotationItemFactoryTest::TestCreateItem_Should_CreateItemAtProvidedPosition()
{
    AnnotationItemFactory itemFactory;
    QPointF position(10, 10);
    ToolTypes tool = ToolTypes::Line;
    auto configInstance = Config::instance();
    configInstance->setToolSize(0, tool);

    auto item = itemFactory.createItem(position, tool);
    item->addPoint(QPoint(20, 20));

    QCOMPARE(item->position(), position);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnNullPtrForUnknownType()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), (ToolTypes)8);

    QVERIFY(item == nullptr);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnAnnotationLine_When_TypeIsLine()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), ToolTypes::Line);

    auto result = dynamic_cast<AnnotationLine*>(item);
    QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnAnnotationArrow_When_TypeIsArrow()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), ToolTypes::Arrow);

    auto result = dynamic_cast<AnnotationArrow*>(item);
    QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnAnnotationRect_When_TypeIsRect()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), ToolTypes::Rect);

    auto result = dynamic_cast<AnnotationRect*>(item);
    QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnAnnotationEllipse_When_TypeIsEllipse()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), ToolTypes::Ellipse);

    auto result = dynamic_cast<AnnotationEllipse*>(item);
    QVERIFY(result != nullptr);
}

void AnnotationItemFactoryTest::TestCreateItem_Should_ReturnAnnotationNumber_When_TypeIsNumber()
{
    AnnotationItemFactory itemFactory;

    auto item = itemFactory.createItem(QPoint(0, 0), ToolTypes::Number);

    auto result = dynamic_cast<AnnotationNumber*>(item);
    QVERIFY(result != nullptr);
}

QTEST_MAIN(AnnotationItemFactoryTest);

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


#include "ItemHelperTest.h"

void ItemHelperTest::TestZValueGreaterThen_Should_ReturnTrue_When_OtherItemHasLowerZValue()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF pos(10, 10);
    AnnotationLine item1(pos, properties);
    AnnotationLine item2(pos, properties);
    item1.setZValue(100);
    item2.setZValue(50);

    auto result = ItemHelper::zValueGreaterThen(&item1, &item2);

    QCOMPARE(result, true);
}

void ItemHelperTest::TestZValueGreaterThen_Should_ReturnFalse_When_OtherItemHasHigherZValue()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF pos(10, 10);
    AnnotationLine item1(pos, properties);
    AnnotationLine item2(pos, properties);
    item1.setZValue(50);
    item2.setZValue(100);

    auto result = ItemHelper::zValueGreaterThen(&item1, &item2);

    QCOMPARE(result, false);
}

void ItemHelperTest::TestZValueGreaterThen_Should_ReturnFalse_When_OtherItemHasEqualZValue()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF pos(10, 10);
    AnnotationLine item1(pos, properties);
    AnnotationLine item2(pos, properties);
    item1.setZValue(100);
    item2.setZValue(100);

    auto result = ItemHelper::zValueGreaterThen(&item1, &item2);

    QCOMPARE(result, false);
}

void ItemHelperTest::TestSortItemsByZValueDesc_Should_SortItemsByZValueInDescendingOrder()
{
    AnnotationProperties properties(Qt::red, 1);
    QPointF pos(10, 10);
    AnnotationLine item1(pos, properties);
    AnnotationLine item2(pos, properties);
    AnnotationLine item3(pos, properties);
    AnnotationLine item4(pos, properties);
    AnnotationLine item5(pos, properties);
    item1.setZValue(100);
    item2.setZValue(80);
    item3.setZValue(2);
    item4.setZValue(60);
    item5.setZValue(90);
    QList<AbstractAnnotationItem *> items;
    items.append(&item3);
    items.append(&item1);
    items.append(&item4);
    items.append(&item5);
    items.append(&item2);

    ItemHelper::sortItemsByZValueDesc(&items);

    QCOMPARE((int) items[0]->zValue(), 100);
    QCOMPARE((int) items[1]->zValue(), 90);
    QCOMPARE((int) items[2]->zValue(), 80);
    QCOMPARE((int) items[3]->zValue(), 60);
    QCOMPARE((int) items[4]->zValue(), 2);
}

QTEST_MAIN(ItemHelperTest);

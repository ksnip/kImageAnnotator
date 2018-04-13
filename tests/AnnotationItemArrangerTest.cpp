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

#include "AnnotationItemArrangerTest.h"

void AnnotationItemArrangerTest::TestBringToFront_Should_BringAllSelectedItemsToFront()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    selectedItems.append(&item2);
    selectedItems.append(&item1);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.bringToFront();

    QCOMPARE((int)item1.zValue(), 3);
    QCOMPARE((int)item2.zValue(), 4);
    QCOMPARE((int)item3.zValue(), 1);
    QCOMPARE((int)item4.zValue(), 2);
}

void AnnotationItemArrangerTest::TestBringForward_Should_MoveAllSelectedItemsOnePositionUp()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    selectedItems.append(&item2);
    selectedItems.append(&item1);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.bringForward();

    QCOMPARE((int)item1.zValue(), 2);
    QCOMPARE((int)item2.zValue(), 3);
    QCOMPARE((int)item3.zValue(), 1);
    QCOMPARE((int)item4.zValue(), 4);
}

void AnnotationItemArrangerTest::TestSendBackward_Should_MoveAllSelectedItemsOnePositionBack()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    selectedItems.append(&item4);
    selectedItems.append(&item3);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.sendBackward();

    QCOMPARE((int)item1.zValue(), 1);
    QCOMPARE((int)item2.zValue(), 4);
    QCOMPARE((int)item3.zValue(), 2);
    QCOMPARE((int)item4.zValue(), 3);
}

void AnnotationItemArrangerTest::TestSendToBack_Should_SendAllSelectedItemToBack()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    selectedItems.append(&item4);
    selectedItems.append(&item3);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.sendToBack();

    QCOMPARE((int)item1.zValue(), 3);
    QCOMPARE((int)item2.zValue(), 4);
    QCOMPARE((int)item3.zValue(), 1);
    QCOMPARE((int)item4.zValue(), 2);
}

void AnnotationItemArrangerTest::TestAnnotationItemArranger_Should_SortAllItemsByZValue_When_PositionHaveBeenSwapped()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    selectedItems.append(&item2);
    selectedItems.append(&item1);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.bringToFront();

    QCOMPARE((int)items[0]->zValue(), 4);
    QCOMPARE((int)items[1]->zValue(), 3);
    QCOMPARE((int)items[2]->zValue(), 2);
    QCOMPARE((int)items[3]->zValue(), 1);
}

void AnnotationItemArrangerTest::TestAnnotationItemArranger_Should_NotSwapAnyPosition_When_NoItemsHaveBeenSelected()
{
    AnnotationProperties properties(Qt::red, 1);
    AnnotationLine item1(QPointF(0, 0), properties);
    AnnotationLine item2(QPointF(0, 0), properties);
    AnnotationLine item3(QPointF(0, 0), properties);
    AnnotationLine item4(QPointF(0, 0), properties);
    item1.setZValue(1);
    item2.setZValue(2);
    item3.setZValue(3);
    item4.setZValue(4);
    QList<AbstractAnnotationItem*> items;
    QList<AbstractAnnotationItem*> selectedItems;
    items.append(&item4);
    items.append(&item3);
    items.append(&item2);
    items.append(&item1);
    AnnotationItemArranger arranger(selectedItems, &items);

    arranger.bringToFront();

    QCOMPARE((int)item1.zValue(), 1);
    QCOMPARE((int)item2.zValue(), 2);
    QCOMPARE((int)item3.zValue(), 3);
    QCOMPARE((int)item4.zValue(), 4);
}

QTEST_MAIN(AnnotationItemArrangerTest);

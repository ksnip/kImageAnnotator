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

#include "AnnotationItemSelectorTest.h"

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_SelectItem_When_ItemUnderProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    AnnotationLine line(p1, properties);
    line.addPoint(p2);
    QList<AbstractAnnotationItem*> items;
    items.append(&line);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(p1 + QPointF(0, 5), &items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 1);
    QCOMPARE(results.first(), &line);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_NotSelectItem_When_ItemNotUnderProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    AnnotationLine line(p1, properties);
    line.addPoint(p2);
    QList<AbstractAnnotationItem*> items;
    items.append(&line);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(p1 + QPointF(0, -5), &items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 0);
    QCOMPARE(results.contains(&line), false);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_UnselectAllItems_When_ProvidedPositionNotOverAnyItem()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;
    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p4 + QPointF(5, 5));
    selector.finishSelectionRectWhenShown(&items);
    QCOMPARE(selector.selectedItems().count(), 2);

    selector.handleSelectionAt(QPointF(0, 0), &items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 0);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_NotUnselectAnyItem_When_ProvidedPositionIsOverSelectedItem()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;
    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p4 + QPointF(5, 5));
    selector.finishSelectionRectWhenShown(&items);
    QCOMPARE(selector.selectedItems().count(), 2);

    selector.handleSelectionAt(p1 + QPointF(0, 5), &items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 2);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_UnselectItemsNotUnderPosition_When_ProvidedPositionIsOverNotSelectedItem()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(12, 12);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;
    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p2 + QPointF(1, 1));
    selector.finishSelectionRectWhenShown(&items);
    QCOMPARE(selector.selectedItems().count(), 1);
    QCOMPARE(selector.selectedItems().contains(&line1), true);
    QCOMPARE(selector.selectedItems().contains(&line2), false);

    selector.handleSelectionAt(p3 + QPointF(2, 2), &items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 1);
    QCOMPARE(results.contains(&line1), false);
    QCOMPARE(results.contains(&line2), true);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_NotShowRect_When_InitialPositionNotOnItem()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    AnnotationLine line(p1, properties);
    line.addPoint(p2);
    QList<AbstractAnnotationItem*> items;
    items.append(&line);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(QPointF(2, 2), &items);

    QCOMPARE(selector.selectedItems().count(), 0);
    QCOMPARE(selector.isSelecting(), true);
}

void AnnotationItemSelectorTest::TestHandleSelectionRectAt_Should_ShowRect_When_InitialPositionOnItem()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    AnnotationLine line(p1, properties);
    line.addPoint(p2);
    QList<AbstractAnnotationItem*> items;
    items.append(&line);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(p1 + QPointF(0, 5), &items);

    QCOMPARE(selector.selectedItems().count(), 1);
    QCOMPARE(selector.isSelecting(), false);
}

void AnnotationItemSelectorTest::TestFinishSelectionRectWhenShown_Should_SelectItems_When_ItemsWithinSelectionRect()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p4 + QPointF(5, 5));
    selector.finishSelectionRectWhenShown(&items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 2);
    QCOMPARE(results.contains(&line1), true);
    QCOMPARE(results.contains(&line2), true);
}

void AnnotationItemSelectorTest::TestFinishSelectionRectWhenShown_Should_SelectOnlyItemWithinSelectionRect()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(25, 25);
    QPointF p4(30, 30);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;

    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p2 + QPointF(5, 5));
    selector.finishSelectionRectWhenShown(&items);

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 1);
    QCOMPARE(results.contains(&line1), true);
    QCOMPARE(results.contains(&line2), false);
}

void AnnotationItemSelectorTest::TestClearSelection_Should_UnselectAllSelectedItems()
{
    AnnotationProperties properties(Qt::red, 3);
    QPointF p1(10, 10);
    QPointF p2(10, 20);
    QPointF p3(15, 15);
    QPointF p4(20, 20);
    AnnotationLine line1(p1, properties);
    AnnotationLine line2(p3, properties);
    line1.addPoint(p2);
    line2.addPoint(p4);
    QList<AbstractAnnotationItem*> items;
    items.append(&line1);
    items.append(&line2);
    AnnotationItemSelector selector;
    selector.handleSelectionAt(p1 + QPointF(-5, -5), &items);
    selector.extendSelectionRectWhenShown(p4 + QPointF(5, 5));
    selector.finishSelectionRectWhenShown(&items);
    QCOMPARE(selector.selectedItems().count(), 2);
    QCOMPARE(selector.selectedItems().contains(&line1), true);
    QCOMPARE(selector.selectedItems().contains(&line2), true);
    QCOMPARE(line1.selected(), true);
    QCOMPARE(line2.selected(), true);

    selector.clearSelection();

    auto results = selector.selectedItems();
    QCOMPARE(results.count(), 0);
    QCOMPARE(line1.selected(), false);
    QCOMPARE(line2.selected(), false);
}

QTEST_MAIN(AnnotationItemSelectorTest);

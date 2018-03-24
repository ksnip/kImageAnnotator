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

#include "AnnotationItemResizerTest.h"

void AnnotationItemResizerTest::TestAttachTo_Should_AttachToAnnotationItem()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);

    itemResizer.attachTo(&lineItem);

    auto result = dynamic_cast<AnnotationLine*>(itemResizer.attachedItem());
    QCOMPARE(result->line(), lineItem.line());
}

void AnnotationItemResizerTest::TestDetach_Should_ClearSelectedItem()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    itemResizer.attachTo(&lineItem);

    itemResizer.detach();

    auto result = itemResizer.attachedItem();
    QVERIFY(result == nullptr);
}

void AnnotationItemResizerTest::TestGrabHandle_Should_GrabHandle_When_ProvidedPointIsAtHandlePosition()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    itemResizer.attachTo(&lineItem);

    itemResizer.grabHandle(p1 + QPointF(2, 2));

    auto isResizing = itemResizer.isResizing();
    QCOMPARE(isResizing, true);
}

void AnnotationItemResizerTest::TestGrabHandle_Should_NotGrabHandle_When_ProvidedPointIsNotAtHandlePosition()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    itemResizer.attachTo(&lineItem);

    itemResizer.grabHandle(QPointF(0, 0));

    auto isResizing = itemResizer.isResizing();
    QCOMPARE(isResizing, false);
}

void AnnotationItemResizerTest::TestGrabHandle_Should_MoveResizeItem_When_HandleGrabbed()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    QPointF p3(30, 30);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    itemResizer.attachTo(&lineItem);
    itemResizer.grabHandle(p1);

    itemResizer.moveHandle(p3);

    auto result = dynamic_cast<AnnotationLine*>(itemResizer.attachedItem());
    QCOMPARE(result->line().p1(), p3);
}

void AnnotationItemResizerTest::TestReleaseHandle_Should_ReleaseHandle()
{
    AnnotationItemResizer itemResizer;
    AnnotationProperties properties(Qt::red, 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    itemResizer.attachTo(&lineItem);
    itemResizer.grabHandle(p1);
    QCOMPARE(itemResizer.isResizing(), true);

    itemResizer.releaseHandle();

    QCOMPARE(itemResizer.isResizing(), false);
}

QTEST_MAIN(AnnotationItemResizerTest);

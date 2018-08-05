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

#include "RectResizeHandlesTest.h"

void RectResizeHandlesTest::TestInitHandles_Should_PositionEightHandles_When_RectItemProvided()
{
    AnnotationProperties properties(Qt::red, 4);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());

    RectResizeHandles rectResizeHandles(&rectItem);

    QCOMPARE(rectResizeHandles.handles().count(), 8);
    QCOMPARE(rectResizeHandles.handles()[0].anchor(), rect.topLeft());
    QCOMPARE(rectResizeHandles.handles()[1].anchor(), QPointF(rect.center().x(), rect.top()));
    QCOMPARE(rectResizeHandles.handles()[2].anchor(), rect.topRight());
    QCOMPARE(rectResizeHandles.handles()[3].anchor(), QPointF(rect.right(), rect.center().y()));
    QCOMPARE(rectResizeHandles.handles()[4].anchor(), rect.bottomRight());
    QCOMPARE(rectResizeHandles.handles()[5].anchor(), QPointF(rect.center().x(), rect.bottom()));
    QCOMPARE(rectResizeHandles.handles()[6].anchor(), rect.bottomLeft());
    QCOMPARE(rectResizeHandles.handles()[7].anchor(), QPointF(rect.left(), rect.center().y()));
}

void RectResizeHandlesTest::TestIndexOfHandleAt_Should_ReturnIndexOfHandle_When_HandleIsAtProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(80, 95));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto resultP1 = rectResizeHandles.indexOfHandleAt(rect.topLeft() + QPointF(2, 2));
    auto resultP2 = rectResizeHandles.indexOfHandleAt(ShapeHelper::rectTop(rect) + QPointF(-2, -2));
    auto resultP3 = rectResizeHandles.indexOfHandleAt(rect.topRight() + QPointF(-2, -2));
    auto resultP4 = rectResizeHandles.indexOfHandleAt(ShapeHelper::rectRight(rect) + QPointF(-2, -2));
    auto resultP5 = rectResizeHandles.indexOfHandleAt(rect.bottomRight() + QPointF(-2, -2));
    auto resultP6 = rectResizeHandles.indexOfHandleAt(ShapeHelper::rectBottom(rect) + QPointF(-2, -2));
    auto resultP7 = rectResizeHandles.indexOfHandleAt(rect.bottomLeft() + QPointF(-2, -2));
    auto resultP8 = rectResizeHandles.indexOfHandleAt(ShapeHelper::rectLeft(rect) + QPointF(-2, -2));

    QCOMPARE(rectResizeHandles.handles().count(), 8);
    QCOMPARE(resultP1, 0);
    QCOMPARE(resultP2, 1);
    QCOMPARE(resultP3, 2);
    QCOMPARE(resultP4, 3);
    QCOMPARE(resultP5, 4);
    QCOMPARE(resultP6, 5);
    QCOMPARE(resultP7, 6);
    QCOMPARE(resultP8, 7);
}

void RectResizeHandlesTest::TestIndexOfHandleAt_Should_NotReturnAnyIndex_When_HandleIsNotAtProvidedPosition()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto resultP1 = rectResizeHandles.indexOfHandleAt(QPointF(50, 50));

    QCOMPARE(rectResizeHandles.handles().count(), 8);
    QCOMPARE(resultP1, -1);
}

void RectResizeHandlesTest::TestHandle_Should_ReturnRectAtIndex_When_HandleAtIndexExists()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto result = rectResizeHandles.handle(2);

    QVERIFY(result != QRectF());
    QCOMPARE(result.anchor(), rect.topRight());
}

void RectResizeHandlesTest::TestHandle_Should_NotReturnRect_When_HandleAtIndexDoesntExists()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto result = rectResizeHandles.handle(10);

    QCOMPARE(result, ResizeHandle());
}

void RectResizeHandlesTest::TestGetCursorForHandle_Should_NotReturnDefaultCursor_When_ProvidedPositionOnHandle()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto result = rectResizeHandles.cursorForPos(rect.bottomLeft());

    QVERIFY(result != CursorHelper::defaultCursor());
}

void RectResizeHandlesTest::TestGetCursorForHandle_Should_ReturnDefaultCursor_When_ProvidedPositionNotOnHandle()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    QPointF otherPos(90, 90);
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);

    auto result = rectResizeHandles.cursorForPos(otherPos);

    QCOMPARE(result, CursorHelper::defaultCursor());
}

void RectResizeHandlesTest::TestUpdate_Should_MoveHandlesToNewPosition()
{
    AnnotationProperties properties(Qt::red, 2);
    QRectF rect(QPointF(10, 15), QPointF(80, 95));
    QRectF newRect(QPointF(60, 75), QPointF(120, 125));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    RectResizeHandles rectResizeHandles(&rectItem);
    QCOMPARE(rectResizeHandles.handles()[0].anchor(), rect.topLeft());
    QCOMPARE(rectResizeHandles.handles()[1].anchor(), ShapeHelper::rectTop(rect));
    QCOMPARE(rectResizeHandles.handles()[2].anchor(), rect.topRight());
    QCOMPARE(rectResizeHandles.handles()[3].anchor(), ShapeHelper::rectRight(rect));
    QCOMPARE(rectResizeHandles.handles()[4].anchor(), rect.bottomRight());
    QCOMPARE(rectResizeHandles.handles()[5].anchor(), ShapeHelper::rectBottom(rect));
    QCOMPARE(rectResizeHandles.handles()[6].anchor(), rect.bottomLeft());
    QCOMPARE(rectResizeHandles.handles()[7].anchor(), ShapeHelper::rectLeft(rect));
    rectItem.setPointAt(newRect.topLeft(), 0);
    rectItem.addPoint(newRect.bottomRight());

    rectResizeHandles.update();

    QCOMPARE(rectResizeHandles.handles()[0].anchor(), newRect.topLeft());
    QCOMPARE(rectResizeHandles.handles()[1].anchor(), ShapeHelper::rectTop(newRect));
    QCOMPARE(rectResizeHandles.handles()[2].anchor(), newRect.topRight());
    QCOMPARE(rectResizeHandles.handles()[3].anchor(), ShapeHelper::rectRight(newRect));
    QCOMPARE(rectResizeHandles.handles()[4].anchor(), newRect.bottomRight());
    QCOMPARE(rectResizeHandles.handles()[5].anchor(), ShapeHelper::rectBottom(newRect));
    QCOMPARE(rectResizeHandles.handles()[6].anchor(), newRect.bottomLeft());
    QCOMPARE(rectResizeHandles.handles()[7].anchor(), ShapeHelper::rectLeft(newRect));
}

QTEST_MAIN(RectResizeHandlesTest);

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

#include "ControlPointsTest.h"

void ControlPointsTest::TestInitPoints_Should_PositionTwoControlPoints_When_LineItemProvided()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ControlPoints controlPoinst(5);

    controlPoinst.initPoints(&lineItem);

    QCOMPARE(controlPoinst.points().count(), 2);
    QCOMPARE(controlPoinst.points()[0].center(), p1);
    QCOMPARE(controlPoinst.points()[1].center(), p2);
}

void ControlPointsTest::TestInitPoints_Should_PositionEightControlPoints_When_RectItemProvided()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QRectF rect(QPointF(10, 15), QPointF(20, 25));
    AnnotationRect rectItem(rect.topLeft(), properties);
    rectItem.addPoint(rect.bottomRight());
    ControlPoints controlPoinst(5);

    controlPoinst.initPoints(&rectItem);

    QCOMPARE(controlPoinst.points().count(), 8);
    QCOMPARE(controlPoinst.points()[0].center(), rect.topLeft());
    QCOMPARE(controlPoinst.points()[1].center(), QPointF(rect.center().x(), rect.top()));
    QCOMPARE(controlPoinst.points()[2].center(), rect.topRight());
    QCOMPARE(controlPoinst.points()[3].center(), QPointF(rect.right(), rect.center().y()));
    QCOMPARE(controlPoinst.points()[4].center(), rect.bottomRight());
    QCOMPARE(controlPoinst.points()[5].center(), QPointF(rect.center().x(), rect.bottom()));
    QCOMPARE(controlPoinst.points()[6].center(), rect.bottomLeft());
    QCOMPARE(controlPoinst.points()[7].center(), QPointF(rect.left(), rect.center().y()));
}

void ControlPointsTest::TestIndexOfPointAt_Should_ReturnIndexOfControlPoint_When_ControlPointIsAtProvidedPoint()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ControlPoints controlPoinst(5);
    controlPoinst.initPoints(&lineItem);

    auto resultP1 = controlPoinst.indexOfPointAt(p1 + QPointF(2, 2));
    auto resultP2 = controlPoinst.indexOfPointAt(p2 + QPointF(-2, -2));

    QCOMPARE(controlPoinst.points().count(), 2);
    QCOMPARE(resultP1, 0);
    QCOMPARE(resultP2, 1);
}

void ControlPointsTest::TestIndexOfPointAt_Should_NotReturnAnyIndex_When_ControlPointIsNotAtProvidedPoint()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ControlPoints controlPoinst(5);
    controlPoinst.initPoints(&lineItem);

    auto resultP1 = controlPoinst.indexOfPointAt(QPointF(50, 50));

    QCOMPARE(controlPoinst.points().count(), 2);
    QCOMPARE(resultP1, -1);
}

void ControlPointsTest::TestPoint_Should_ReturnRectAtIndex_When_PointAtIndexExists()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ControlPoints controlPoinst(5);
    controlPoinst.initPoints(&lineItem);

    auto result = controlPoinst.point(1);

    QVERIFY(result != QRectF());
    QCOMPARE(result.center(), p2);
}

void ControlPointsTest::TestPoint_Should_NotReturnRect_When_PointAtIndexDoesntExists()
{
    AnnotationProperties properties(QColor(QStringLiteral("Red")), 2);
    QPointF p1(10, 10);
    QPointF p2(20, 20);
    AnnotationLine lineItem(p1, properties);
    lineItem.addPoint(p2);
    ControlPoints controlPoinst(5);
    controlPoinst.initPoints(&lineItem);

    auto result = controlPoinst.point(3);

    QCOMPARE(result, QRectF());
}

QTEST_MAIN(ControlPointsTest);

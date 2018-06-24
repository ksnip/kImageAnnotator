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


#include "ShapeHelperTest.h"

void ShapeHelperTest::TestRectTop_Should_ReturnPointAtTopCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto top = ShapeHelper::rectTop(rect);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top()));
}

void ShapeHelperTest::TestRectRight_Should_ReturnPointAtRightCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto right = ShapeHelper::rectRight(rect);

    QCOMPARE(right, QPointF(rect.right(), rect.center().y()));
}

void ShapeHelperTest::TestRectLeft_Should_ReturnPointAtLeftCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto left = ShapeHelper::rectLeft(rect);

    QCOMPARE(left, QPointF(rect.left(), rect.center().y()));
}

void ShapeHelperTest::TestRectBottom_Should_ReturnPointAtBottomCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto bottom = ShapeHelper::rectBottom(rect);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom()));
}

void ShapeHelperTest::TestRectTopWithOffset_Should_ReturnPointAtTopWithAddedOffset_When_TopSmallerThenBottom()
{
    QRectF rect(10, 10, 50, 50);
    rect.setTop(rect.bottom() + 20);
    auto offset = 5;

    auto top = ShapeHelper::rectTopWithOffset(rect, offset);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top() + offset));
}

void ShapeHelperTest::TestRectTopWithOffset_Should_ReturnPointAtTopWithSubtractedOffset_When_TopLargerThenBottom()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto top = ShapeHelper::rectTopWithOffset(rect, offset);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top() - offset));
}

void ShapeHelperTest::TestRectRightWithOffset_Should_ReturnPointAtRightWithSubtracedOffset_When_RightSmallerThenLeft()
{
    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() - 20);
    auto offset = 5;

    auto right = ShapeHelper::rectRightWithOffset(rect, offset);

    QCOMPARE(right, QPointF(rect.right() - offset, rect.center().y()));
}

void ShapeHelperTest::TestRectRightWithOffset_Should_ReturnPointAtRightWithAddedOffset_When_RightLargerThenLeft()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto right = ShapeHelper::rectRightWithOffset(rect, offset);

    QCOMPARE(right, QPointF(rect.right() + offset, rect.center().y()));
}

void ShapeHelperTest::TestRectBottomWithOffset_Should_ReturnPointAtBottomWithSubtracedOffset_When_BottomSmallerThenTop()
{
    QRectF rect(10, 10, 50, 50);
    rect.setBottom(rect.top() - 20);
    auto offset = 5;

    auto bottom = ShapeHelper::rectBottomWithOffset(rect, offset);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom() - offset));
}

void ShapeHelperTest::TestRectBottomWithOffset_Should_ReturnPointAtBottomWithAddedOffset_When_BottomLargerThenTop()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto bottom = ShapeHelper::rectBottomWithOffset(rect, offset);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom() + offset));
}

void ShapeHelperTest::TestRectLeftWithOffset_Should_ReturnPointAtLeftWithAddedOffset_When_LeftSmallerThenRight()
{
    QRectF rect(10, 10, 50, 50);
    rect.setLeft(rect.right() + 20);
    auto offset = 5;

    auto left = ShapeHelper::rectLeftWithOffset(rect, offset);

    QCOMPARE(left, QPointF(rect.left() + offset, rect.center().y()));
}

void ShapeHelperTest::TestRectLeftWithOffset_Should_ReturnPointAtLeftWithSubtracedOffset_When_LeftLargerThenRight()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto left = ShapeHelper::rectLeftWithOffset(rect, offset);

    QCOMPARE(left, QPointF(rect.left() - offset, rect.center().y()));
}

void ShapeHelperTest::TestRectTopLeftWithOffset_Should_ReturnPointWithCorrectOffset()
{
    QFETCH(int, addToRight);
    QFETCH(int, addToBottom);
    QFETCH(int, expectedOffsetX);
    QFETCH(int, expectedOffsetY);

    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() + addToRight);
    rect.setBottom(rect.top() + addToBottom);
    auto offset = 5;

    auto topLeft = ShapeHelper::rectTopLeftWithOffset(rect, offset);

    QCOMPARE(topLeft, QPointF(rect.topLeft().x() + expectedOffsetX, rect.topLeft().y() + expectedOffsetY));
}

void ShapeHelperTest::TestRectTopLeftWithOffset_Should_ReturnPointWithCorrectOffset_data()
{
    QTest::addColumn<int>("addToRight");
    QTest::addColumn<int>("addToBottom");
    QTest::addColumn<int>("expectedOffsetX");
    QTest::addColumn<int>("expectedOffsetY");

    QTest::newRow("set1") << 10 << 10 << -5 << -5;
    QTest::newRow("set2") << -10 << 10 << 5 << -5;
    QTest::newRow("set3") << 10 << -10 << -5 << 5;
    QTest::newRow("set4") << -10 << -10 << 5 << 5;
}

void ShapeHelperTest::TestRectTopRightWithOffset_Should_ReturnPointWithCorrectOffset()
{
    QFETCH(int, addToRight);
    QFETCH(int, addToBottom);
    QFETCH(int, expectedOffsetX);
    QFETCH(int, expectedOffsetY);

    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() + addToRight);
    rect.setBottom(rect.top() + addToBottom);
    auto offset = 5;

    auto topRight = ShapeHelper::rectTopRightWithOffset(rect, offset);

    QCOMPARE(topRight, QPointF(rect.topRight().x() + expectedOffsetX, rect.topRight().y() + expectedOffsetY));
}

void ShapeHelperTest::TestRectTopRightWithOffset_Should_ReturnPointWithCorrectOffset_data()
{
    QTest::addColumn<int>("addToRight");
    QTest::addColumn<int>("addToBottom");
    QTest::addColumn<int>("expectedOffsetX");
    QTest::addColumn<int>("expectedOffsetY");

    QTest::newRow("set1") << 10 << 10 << 5 << -5;
    QTest::newRow("set2") << -10 << 10 << -5 << -5;
    QTest::newRow("set3") << 10 << -10 << 5 << 5;
    QTest::newRow("set4") << -10 << -10 << -5 << 5;
}

void ShapeHelperTest::TestRectBottomLeftWithOffset_Should_ReturnPointWithCorrectOffset()
{
    QFETCH(int, addToRight);
    QFETCH(int, addToBottom);
    QFETCH(int, expectedOffsetX);
    QFETCH(int, expectedOffsetY);

    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() + addToRight);
    rect.setBottom(rect.top() + addToBottom);
    auto offset = 5;

    auto bottomLeft = ShapeHelper::rectBottomLeftWithOffset(rect, offset);

    QCOMPARE(bottomLeft, QPointF(rect.bottomLeft().x() + expectedOffsetX, rect.bottomLeft().y() + expectedOffsetY));
}

void ShapeHelperTest::TestRectBottomLeftWithOffset_Should_ReturnPointWithCorrectOffset_data()
{
    QTest::addColumn<int>("addToRight");
    QTest::addColumn<int>("addToBottom");
    QTest::addColumn<int>("expectedOffsetX");
    QTest::addColumn<int>("expectedOffsetY");

    QTest::newRow("set1") << 10 << 10 << -5 << 5;
    QTest::newRow("set2") << -10 << 10 << 5 << 5;
    QTest::newRow("set3") << 10 << -10 << -5 << -5;
    QTest::newRow("set4") << -10 << -10 << 5 << -5;
}

void ShapeHelperTest::TestRectBottomRightWithOffset_Should_ReturnPointWithCorrectOffset()
{
    QFETCH(int, addToRight);
    QFETCH(int, addToBottom);
    QFETCH(int, expectedOffsetX);
    QFETCH(int, expectedOffsetY);

    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() + addToRight);
    rect.setBottom(rect.top() + addToBottom);
    auto offset = 5;

    auto bottomRight = ShapeHelper::rectBottomRightWithOffset(rect, offset);

    QCOMPARE(bottomRight, QPointF(rect.bottomRight().x() + expectedOffsetX, rect.bottomRight().y() + expectedOffsetY));
}

void ShapeHelperTest::TestRectBottomRightWithOffset_Should_ReturnPointWithCorrectOffset_data()
{
    QTest::addColumn<int>("addToRight");
    QTest::addColumn<int>("addToBottom");
    QTest::addColumn<int>("expectedOffsetX");
    QTest::addColumn<int>("expectedOffsetY");

    QTest::newRow("set1") << 10 << 10 << 5 << 5;
    QTest::newRow("set2") << -10 << 10 << -5 << 5;
    QTest::newRow("set3") << 10 << -10 << 5 << -5;
    QTest::newRow("set4") << -10 << -10 << -5 << -5;
}

void ShapeHelperTest::TestExtendLine_Should_ReturnNewLineExtendBySizeWithSameAngle()
{
    QLineF line(10, 10, 20, 20);
    auto extendBy = 12;

    auto result = ShapeHelper::extendLine(line, extendBy);

    QLineF lineExtendP1(line.p2(), line.p1());
    lineExtendP1.setLength(line.length() + extendBy / 2);
    lineExtendP1.setLine(lineExtendP1.p2().x(), lineExtendP1.p2().y(), lineExtendP1.p1().x(), lineExtendP1.p1().y());
    auto lineExtendP2 = line;
    lineExtendP2.setLength(line.length() + extendBy / 2);
    QCOMPARE(result.length(), line.length() + extendBy);
    QCOMPARE(result.angle(), line.angle());
    QCOMPARE(result.p1(), lineExtendP1.p1());
    QCOMPARE(result.p2(), lineExtendP2.p2());
}

void ShapeHelperTest::TestRectPointAtIndex_Should_ReturnPointAtIndexPosition()
{
    QFETCH(QRectF, rect);
    QFETCH(int, index);
    QFETCH(QPointF, expected);

    auto result = ShapeHelper::rectPointAtIndex(rect, index);

    QCOMPARE(result, expected);
}

void ShapeHelperTest::TestRectPointAtIndex_Should_ReturnPointAtIndexPosition_data()
{
    QTest::addColumn<QRectF>("rect");
    QTest::addColumn<int>("index");
    QTest::addColumn<QPointF>("expected");

    QTest::newRow("set1") << QRectF(10, 10, 10, 10) << 0 << QPointF(10, 10);
    QTest::newRow("set2") << QRectF(10, 10, 10, 10) << 1 << QPointF(15, 10);
    QTest::newRow("set3") << QRectF(10, 10, 10, 10) << 2 << QPointF(20, 10);
    QTest::newRow("set4") << QRectF(10, 10, 10, 10) << 3 << QPointF(20, 15);
    QTest::newRow("set5") << QRectF(10, 10, 10, 10) << 4 << QPointF(20, 20);
    QTest::newRow("set6") << QRectF(10, 10, 10, 10) << 5 << QPointF(15, 20);
    QTest::newRow("set7") << QRectF(10, 10, 10, 10) << 6 << QPointF(10, 20);
    QTest::newRow("set8") << QRectF(10, 10, 10, 10) << 7 << QPointF(10, 15);
    QTest::newRow("set8") << QRectF(10, 10, 10, 10) << 8 << QPointF();
}

void ShapeHelperTest::TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint()
{
    QFETCH(QRectF, rectInitial);
    QFETCH(int, index);
    QFETCH(QPointF, point);
    QFETCH(QRectF, expected);

    auto result = ShapeHelper::setRectPointAtIndex(rectInitial, index, point);

    QCOMPARE(result, expected);
}

void ShapeHelperTest::TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint_data()
{
    QTest::addColumn<QRectF>("rectInitial");
    QTest::addColumn<int>("index");
    QTest::addColumn<QPointF>("point");
    QTest::addColumn<QRectF>("expected");

    QTest::newRow("set1") << QRectF(10, 10, 10, 10) << 0 << QPointF(5, 5) << QRectF(5, 5, 15, 15);
    QTest::newRow("set2") << QRectF(10, 10, 10, 10) << 1 << QPointF(15, 5) << QRectF(10, 5, 10, 15);
    QTest::newRow("set3") << QRectF(10, 10, 10, 10) << 2 << QPointF(25, 5) << QRectF(10, 5, 15, 15);
    QTest::newRow("set4") << QRectF(10, 10, 10, 10) << 3 << QPointF(25, 15) << QRectF(10, 10, 15, 10);
    QTest::newRow("set5") << QRectF(10, 10, 10, 10) << 4 << QPointF(25, 25) << QRectF(10, 10, 15, 15);
    QTest::newRow("set6") << QRectF(10, 10, 10, 10) << 5 << QPointF(15, 25) << QRectF(10, 10, 10, 15);
    QTest::newRow("set7") << QRectF(10, 10, 10, 10) << 6 << QPointF(5, 25) << QRectF(5, 10, 15, 15);
    QTest::newRow("set8") << QRectF(10, 10, 10, 10) << 7 << QPointF(5, 15) << QRectF(5, 10, 15, 10);
    QTest::newRow("set8") << QRectF(10, 10, 10, 10) << 8 << QPointF(60, 60) << QRectF(10, 10, 10, 10);
}

QTEST_MAIN(ShapeHelperTest);

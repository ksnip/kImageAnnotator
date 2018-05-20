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

void ShapeHelperTest::TestRectTop_ReturnsPointAtTopCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto top = ShapeHelper::rectTop(rect);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top()));
}

void ShapeHelperTest::TestRectRight_ReturnsPointAtRightCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto right = ShapeHelper::rectRight(rect);

    QCOMPARE(right, QPointF(rect.right(), rect.center().y()));
}

void ShapeHelperTest::TestRectLeft_ReturnsPointAtLeftCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto left = ShapeHelper::rectLeft(rect);

    QCOMPARE(left, QPointF(rect.left(), rect.center().y()));
}

void ShapeHelperTest::TestRectBottom_ReturnsPointAtBottomCentered()
{
    QRectF rect(10, 10, 50, 50);

    auto bottom = ShapeHelper::rectBottom(rect);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom()));
}

void ShapeHelperTest::TestRectTopWithOffset_ReturnsPointAtTopWithAddedOffset_When_TopSmallerThenBottom()
{
    QRectF rect(10, 10, 50, 50);
    rect.setTop(rect.bottom() + 20);
    auto offset = 5;

    auto top = ShapeHelper::rectTopWithOffset(rect, offset);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top() + offset));
}

void ShapeHelperTest::TestRectTopWithOffset_ReturnsPointAtTopWithSubtractedOffset_When_TopLargerThenBottom()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto top = ShapeHelper::rectTopWithOffset(rect, offset);

    QCOMPARE(top, QPointF(rect.center().x(), rect.top() - offset));
}

void ShapeHelperTest::TestRectRightWithOffset_ReturnsPointAtRightWithSubtracedOffset_When_RightSmallerThenLeft()
{
    QRectF rect(10, 10, 50, 50);
    rect.setRight(rect.left() - 20);
    auto offset = 5;

    auto right = ShapeHelper::rectRightWithOffset(rect, offset);

    QCOMPARE(right, QPointF(rect.right() - offset, rect.center().y()));
}

void ShapeHelperTest::TestRectRightWithOffset_ReturnsPointAtRightWithAddedOffset_When_RightLargerThenLeft()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto right = ShapeHelper::rectRightWithOffset(rect, offset);

    QCOMPARE(right, QPointF(rect.right() + offset, rect.center().y()));
}

void ShapeHelperTest::TestRectBottomWithOffset_ReturnsPointAtBottomWithSubtracedOffset_When_BottomSmallerThenTop()
{
    QRectF rect(10, 10, 50, 50);
    rect.setBottom(rect.top() - 20);
    auto offset = 5;

    auto bottom = ShapeHelper::rectBottomWithOffset(rect, offset);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom() - offset));
}

void ShapeHelperTest::TestRectBottomWithOffset_ReturnsPointAtBottomWithAddedOffset_When_BottomLargerThenTop()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto bottom = ShapeHelper::rectBottomWithOffset(rect, offset);

    QCOMPARE(bottom, QPointF(rect.center().x(), rect.bottom() + offset));
}

void ShapeHelperTest::TestRectLeftWithOffset_ReturnsPointAtLeftWithAddedOffset_When_LeftSmallerThenRight()
{
    QRectF rect(10, 10, 50, 50);
    rect.setLeft(rect.right() + 20);
    auto offset = 5;

    auto left = ShapeHelper::rectLeftWithOffset(rect, offset);

    QCOMPARE(left, QPointF(rect.left() + offset, rect.center().y()));
}

void ShapeHelperTest::TestRectLeftWithOffset_ReturnsPointAtLeftWithSubtracedOffset_When_LeftLargerThenRight()
{
    QRectF rect(10, 10, 50, 50);
    auto offset = 5;

    auto left = ShapeHelper::rectLeftWithOffset(rect, offset);

    QCOMPARE(left, QPointF(rect.left() - offset, rect.center().y()));
}

void ShapeHelperTest::TestRectTopLeftWithOffset_ReturnPointWithCorrectOffset()
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

void ShapeHelperTest::TestRectTopLeftWithOffset_ReturnPointWithCorrectOffset_data()
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

void ShapeHelperTest::TestRectTopRightWithOffset_ReturnPointWithCorrectOffset()
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

void ShapeHelperTest::TestRectTopRightWithOffset_ReturnPointWithCorrectOffset_data()
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

void ShapeHelperTest::TestRectBottomLeftWithOffset_ReturnPointWithCorrectOffset()
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

void ShapeHelperTest::TestRectBottomLeftWithOffset_ReturnPointWithCorrectOffset_data()
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

void ShapeHelperTest::TestRectBottomRightWithOffset_ReturnPointWithCorrectOffset()
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

void ShapeHelperTest::TestRectBottomRightWithOffset_ReturnPointWithCorrectOffset_data()
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

QTEST_MAIN(ShapeHelperTest);

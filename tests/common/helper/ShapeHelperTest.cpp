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

QTEST_MAIN(ShapeHelperTest);

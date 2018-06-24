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

#ifndef KIMAGEANNOTATOR_SHAPEHELPERTEST
#define KIMAGEANNOTATOR_SHAPEHELPERTEST

#include <QtTest>

#include "../../../src/common/helper/ShapeHelper.h"

class ShapeHelperTest : public QObject
{
Q_OBJECT

private slots:
    void TestRectTop_ReturnsPointAtTopCentered();
    void TestRectRight_ReturnsPointAtRightCentered();
    void TestRectLeft_ReturnsPointAtLeftCentered();
    void TestRectBottom_ReturnsPointAtBottomCentered();
    void TestRectTopWithOffset_ReturnsPointAtTopWithAddedOffset_When_TopSmallerThenBottom();
    void TestRectTopWithOffset_ReturnsPointAtTopWithSubtractedOffset_When_TopLargerThenBottom();
    void TestRectRightWithOffset_ReturnsPointAtRightWithSubtracedOffset_When_RightSmallerThenLeft();
    void TestRectRightWithOffset_ReturnsPointAtRightWithAddedOffset_When_RightLargerThenLeft();
    void TestRectBottomWithOffset_ReturnsPointAtBottomWithSubtracedOffset_When_BottomSmallerThenTop();
    void TestRectBottomWithOffset_ReturnsPointAtBottomWithAddedOffset_When_BottomLargerThenTop();
    void TestRectLeftWithOffset_ReturnsPointAtLeftWithAddedOffset_When_LeftSmallerThenRight();
    void TestRectLeftWithOffset_ReturnsPointAtLeftWithSubtracedOffset_When_LeftLargerThenRight();
    void TestRectTopLeftWithOffset_ReturnPointWithCorrectOffset();
    void TestRectTopLeftWithOffset_ReturnPointWithCorrectOffset_data();
    void TestRectTopRightWithOffset_ReturnPointWithCorrectOffset();
    void TestRectTopRightWithOffset_ReturnPointWithCorrectOffset_data();
    void TestRectBottomLeftWithOffset_ReturnPointWithCorrectOffset();
    void TestRectBottomLeftWithOffset_ReturnPointWithCorrectOffset_data();
    void TestRectBottomRightWithOffset_ReturnPointWithCorrectOffset();
    void TestRectBottomRightWithOffset_ReturnPointWithCorrectOffset_data();
    void TestExtendLine_Should_ReturnNewLineExtendBySizeWithSameAngle();
    void TestRectPointAtIndex_Should_ReturnPointAtIndexPosition();
    void TestRectPointAtIndex_Should_ReturnPointAtIndexPosition_data();
    void TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint();
    void TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint_data();
};

#endif //KIMAGEANNOTATOR_SHAPEHELPERTEST

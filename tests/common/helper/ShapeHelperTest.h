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

#ifndef KIMAGEANNOTATOR_SHAPEHELPERTEST_H
#define KIMAGEANNOTATOR_SHAPEHELPERTEST_H

#include <QtTest>

#include "../../../src/common/helper/ShapeHelper.h"

class ShapeHelperTest : public QObject
{
Q_OBJECT

private slots:
    void TestRectTop_Should_ReturnPointAtTopCentered();
    void TestRectRight_Should_ReturnPointAtRightCentered();
    void TestRectLeft_Should_ReturnPointAtLeftCentered();
    void TestRectBottom_Should_ReturnPointAtBottomCentered();
    void TestRectTopWithOffset_Should_ReturnPointAtTopWithAddedOffset_When_TopSmallerThenBottom();
    void TestRectTopWithOffset_Should_ReturnPointAtTopWithSubtractedOffset_When_TopLargerThenBottom();
    void TestRectRightWithOffset_Should_ReturnPointAtRightWithSubtracedOffset_When_RightSmallerThenLeft();
    void TestRectRightWithOffset_Should_ReturnPointAtRightWithAddedOffset_When_RightLargerThenLeft();
    void TestRectBottomWithOffset_Should_ReturnPointAtBottomWithSubtracedOffset_When_BottomSmallerThenTop();
    void TestRectBottomWithOffset_Should_ReturnPointAtBottomWithAddedOffset_When_BottomLargerThenTop();
    void TestRectLeftWithOffset_Should_ReturnPointAtLeftWithAddedOffset_When_LeftSmallerThenRight();
    void TestRectLeftWithOffset_Should_ReturnPointAtLeftWithSubtracedOffset_When_LeftLargerThenRight();
    void TestRectTopLeftWithOffset_Should_ReturnPointWithCorrectOffset();
    void TestRectTopLeftWithOffset_Should_ReturnPointWithCorrectOffset_data();
    void TestRectTopRightWithOffset_Should_ReturnPointWithCorrectOffset();
    void TestRectTopRightWithOffset_Should_ReturnPointWithCorrectOffset_data();
    void TestRectBottomLeftWithOffset_Should_ReturnPointWithCorrectOffset();
    void TestRectBottomLeftWithOffset_Should_ReturnPointWithCorrectOffset_data();
    void TestRectBottomRightWithOffset_Should_ReturnPointWithCorrectOffset();
    void TestRectBottomRightWithOffset_Should_ReturnPointWithCorrectOffset_data();
    void TestExtendLine_Should_ReturnNewLineExtendBySizeWithSameAngle();
    void TestRectPointAtIndex_Should_ReturnPointAtIndexPosition();
    void TestRectPointAtIndex_Should_ReturnPointAtIndexPosition_data();
    void TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint();
    void TestSetRectPointAtIndex_Should_SetRectPointAtIndexToProvidedPoint_data();
    void TestSmoothOut_Should_RetunSamePath_When_PathHasOnlyThreeElement();
};

#endif //KIMAGEANNOTATOR_SHAPEHELPERTEST_H

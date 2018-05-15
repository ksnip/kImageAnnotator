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

#ifndef MATHHELPERTEST_H
#define MATHHELPERTEST_H

#include <QtTest>

#include "../../../src/common/helper/MathHelper.h"

class MathHelperTest : public QObject
{
Q_OBJECT
private slots:
    void TestRoundAngleTo_Should_ReturnAngleRoundedUpToIncrement();
    void TestRoundAngleTo_Should_ReturnAngleRoundedUpToIncrement_data();
    void TestSmallerValue_Should_AlwaysSmallerOfTwoValues();
    void TestSmallerValue_Should_AlwaysSmallerOfTwoValues_data();
    void TestRectTop_ReturnsPointAtTopCentered();
    void TestRectRight_ReturnsPointAtRightCentered();
    void TestRectLeft_ReturnsPointAtLeftCentered();
    void TestRectBottom_ReturnsPointAtBottomCentered();
};

#endif // MATHHELPERTEST_H

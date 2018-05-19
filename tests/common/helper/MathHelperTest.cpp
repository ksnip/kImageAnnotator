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

#include "MathHelperTest.h"

void MathHelperTest::TestRoundAngleTo_Should_ReturnAngleRoundedUpToIncrement()
{
    QFETCH(qreal, angle);
    QFETCH(qreal, increment);
    QFETCH(qreal, result);

    auto newAngle = MathHelper::roundAngleTo(angle, increment);

    QCOMPARE(newAngle, result);
}

void MathHelperTest::TestRoundAngleTo_Should_ReturnAngleRoundedUpToIncrement_data()
{
    QTest::addColumn<qreal>("angle");
    QTest::addColumn<qreal>("increment");
    QTest::addColumn<qreal>("result");

    QTest::newRow("set1") << 50.0 << 45.0 << 45.0;
    QTest::newRow("set2") << 87.0 << 45.0 << 90.0;
    QTest::newRow("set3") << 0.0 << 45.0 << 0.0;
    QTest::newRow("set4") << 355.0 << 45.0 << 360.0;
    QTest::newRow("set5") << 360.0 << 45.0 << 360.0;
    QTest::newRow("set6") << -2.0 << 45.0 << 0.0;
}

void MathHelperTest::TestSmallerValue_Should_AlwaysSmallerOfTwoValues()
{
    QFETCH(qreal, width);
    QFETCH(qreal, height);
    QFETCH(qreal, result);

    auto smallest = MathHelper::smallerValue(width, height);

    QCOMPARE(smallest, result);
}

void MathHelperTest::TestSmallerValue_Should_AlwaysSmallerOfTwoValues_data()
{
    QTest::addColumn<qreal>("width");
    QTest::addColumn<qreal>("height");
    QTest::addColumn<qreal>("result");

    QTest::newRow("set1") << 50.0 << 49.0 << 49.0;
    QTest::newRow("set2") << -87.0 << 1.0 << -1.0;
    QTest::newRow("set3") << 0.0 << -1.0 << 0.0;
    QTest::newRow("set4") << 400.0 << -500.0 << 400.0;
    QTest::newRow("set5") << -3.0 << 2.0 << -2.0;
    QTest::newRow("set6") << -2.0 << 2.0 << -2.0;
}

QTEST_MAIN(MathHelperTest);

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

#ifndef CONTROLPOINTSTEST_H
#define CONTROLPOINTSTEST_H

#include <QtTest>

#include "../src/annotationItems/ControlPoints.h"
#include "../src/annotationItems/AnnotationLine.h"
#include "../src/annotationItems/AnnotationRect.h"

class ControlPointsTest : public QObject
{
Q_OBJECT

private slots:
    void TestInitPoints_Should_PositionTwoControlPoints_When_LineItemProvided();
    void TestInitPoints_Should_PositionEightControlPoints_When_RectItemProvided();
    void TestIndexOfPointAt_Should_ReturnIndexOfControlPoint_When_ControlPointIsAtProvidedPoint();
    void TestIndexOfPointAt_Should_NotReturnAnyIndex_When_ControlPointIsNotAtProvidedPoint();
};

#endif // CONTROLPOINTSTEST_H

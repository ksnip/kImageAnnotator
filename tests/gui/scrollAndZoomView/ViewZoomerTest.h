/*
 * Copyright (C) 2026 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_VIEWZOOMERTEST_H
#define KIMAGEANNOTATOR_VIEWZOOMERTEST_H

#include <QtTest>
#include <QGraphicsView>

#include "tests/utils/TestRunner.h"
#include "src/gui/scrollAndZoomView/ViewZoomer.h"

using kImageAnnotator::ViewZoomer;

class ViewZoomerTest : public QObject
{
Q_OBJECT

private slots:
	void TestSetZoomValue_Should_UseValueAsEntered();
	void TestZoom_Should_StepToNextMultipleOfStep_When_ZoomingIn();
	void TestZoom_Should_StepToNextMultipleOfStep_When_ZoomingOut();
	void TestZoom_Should_NotGoBelowMinimum();
};

#endif // KIMAGEANNOTATOR_VIEWZOOMERTEST_H

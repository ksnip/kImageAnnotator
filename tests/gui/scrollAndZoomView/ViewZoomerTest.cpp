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

#include "ViewZoomerTest.h"

void ViewZoomerTest::TestSetZoomValue_Should_UseValueAsEntered()
{
	QGraphicsView view;
	ViewZoomer zoomer(&view);

	zoomer.setZoomValue(0.75);

	QCOMPARE(zoomer.zoomValue(), 0.75);
}

void ViewZoomerTest::TestZoom_Should_StepToNextMultipleOfStep_When_ZoomingIn()
{
	QGraphicsView view;
	ViewZoomer zoomer(&view);
	zoomer.setZoomValue(0.75);

	zoomer.zoom(0.1);
	QCOMPARE(zoomer.zoomValue(), 0.8);

	zoomer.zoom(0.1);
	QCOMPARE(zoomer.zoomValue(), 0.9);
}

void ViewZoomerTest::TestZoom_Should_StepToNextMultipleOfStep_When_ZoomingOut()
{
	QGraphicsView view;
	ViewZoomer zoomer(&view);
	zoomer.setZoomValue(0.75);

	zoomer.zoom(-0.1);
	QCOMPARE(zoomer.zoomValue(), 0.7);

	zoomer.zoom(-0.1);
	QCOMPARE(zoomer.zoomValue(), 0.6);
}

void ViewZoomerTest::TestZoom_Should_NotGoBelowMinimum()
{
	QGraphicsView view;
	ViewZoomer zoomer(&view);
	zoomer.setZoomValue(0.1);

	zoomer.zoom(-0.1);

	QCOMPARE(zoomer.zoomValue(), 0.1);
}

TEST_MAIN(ViewZoomerTest);

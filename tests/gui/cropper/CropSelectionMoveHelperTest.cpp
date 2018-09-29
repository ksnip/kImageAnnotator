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


#include "CropSelectionMoveHelperTest.h"

void CropSelectionMoveHelperTest::TestGrabSelection_Should_GrabSelection_WhenPositionWithinSelection()
{
	QRectF selection(100, 100, 300, 300);
	QPointF position(150, 150);
	CropSelectionMoveHelper moveHelper;

	moveHelper.grabSelection(position, selection);

	QCOMPARE(moveHelper.isSelectionGabbed(), true);
}

void CropSelectionMoveHelperTest::TestGrabSelection_Should_NotGrabSelection_WhenPositionOutsideSelection()
{
	QRectF selection(100, 100, 300, 300);
	QPointF position(50, 50);
	CropSelectionMoveHelper moveHelper;

	moveHelper.grabSelection(position, selection);

	QCOMPARE(moveHelper.isSelectionGabbed(), false);
}

void CropSelectionMoveHelperTest::TestGrabSelection_Should_SetCorrectOffset()
{
	QRectF selection(100, 100, 300, 300);
	QPointF position(150, 150);
	CropSelectionMoveHelper moveHelper;

	moveHelper.grabSelection(position, selection);

	QCOMPARE(moveHelper.grabOffset(), QPointF(50, 50));
}

void CropSelectionMoveHelperTest::TestReleaseSelection_Should_ReleaseSelection()
{
	QRectF selection(100, 100, 300, 300);
	QPointF position(150, 150);
	CropSelectionMoveHelper moveHelper;
	moveHelper.grabSelection(position, selection);
	QCOMPARE(moveHelper.isSelectionGabbed(), true);

	moveHelper.releaseSelection();

	QCOMPARE(moveHelper.isSelectionGabbed(), false);
}

QTEST_MAIN(CropSelectionMoveHelperTest);



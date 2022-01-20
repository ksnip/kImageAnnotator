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


#include "CropSelectionRestrictorTest.h"

void CropSelectionRestrictorTest::TestRestrictResize_Should_NotChangeResize_When_NewSizeSmallerThenMaxRect()
{
	QRectF newRect(50, 50, 400, 400);
	QRectF currentRect(100, 100, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, maxRect);

	QCOMPARE(resizeRect, QRectF(50, 50, 400, 400));
}

void CropSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewSizeLargerThenMaxRect()
{
	QRectF newRect(0, 0, 600, 600);
	QRectF currentRect(100, 100, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, maxRect);

	QCOMPARE(resizeRect, QRectF(0, 0, 500, 500));
}

void CropSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewPositionIsOutsideMaxRect()
{
	QRectF newRect(-50, -50, 400, 400);
	QRectF currentRect(100, 100, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, maxRect);

	QCOMPARE(resizeRect, QRectF(0, 0, 350, 350));
}

void CropSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewPositionHasNegativeWidth()
{
	QRectF newRect(50, 50, -400, 400);
	QRectF currentRect(50, 50, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, maxRect);

	QCOMPARE(resizeRect, QRectF(50, 50, 0, 400));
}

void CropSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewPositionHasNegativeHeight()
{
	QRectF newRect(50, 50, 400, -400);
	QRectF currentRect(50, 50, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, maxRect);

	QCOMPARE(resizeRect, QRectF(50, 50, 400, 0));
}

void CropSelectionRestrictorTest::TestRestrictMove_Should_NotChangeMove_When_NewPositionAndSizeWithinMaxRect()
{
	QRectF newRect(50, 50, 400, 400);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, maxRect);

	QCOMPARE(resizeRect, QRectF(50, 50, 400, 400));
}

void CropSelectionRestrictorTest::TestRestrictMove_Should_ChangeMove_When_NewPositionOutsideMaxRect()
{
	QRectF newRect(-50, -50, 200, 200);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, maxRect);

	QCOMPARE(resizeRect, QRectF(0, 0, 200, 200));
}

void CropSelectionRestrictorTest::TestRestrictMove_Should_ChangeMove_When_NewSizeOutsideMaxRect()
{
	QRectF newRect(300, 300, 300, 300);
	QRectF maxRect(0, 0, 500, 500);
	CropSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, maxRect);

	QCOMPARE(resizeRect, QRectF(200, 200, 300, 300));
}

TEST_MAIN(CropSelectionRestrictorTest);

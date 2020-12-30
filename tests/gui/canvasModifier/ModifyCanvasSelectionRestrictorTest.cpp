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


#include "ModifyCanvasSelectionRestrictorTest.h"

void ModifyCanvasSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewSizeSmallerThenMinRect()
{
	QRectF newRect(50, 50, 400, 400);
	QRectF currentRect(100, 100, 200, 200);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, minRect);

	QCOMPARE(resizeRect, minRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictResize_Should_NotChangeResize_When_NewSizeLargerThenMinRect()
{
	QRectF newRect(0, 0, 600, 600);
	QRectF currentRect(100, 100, 200, 200);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, minRect);

	QCOMPARE(resizeRect, newRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictResize_Should_NotChangeResize_When_NewPositionIsOutsideMinRect()
{
	QRectF newRect(-50, -50, 400, 400);
	QRectF currentRect(100, 100, 200, 200);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, minRect);

	QCOMPARE(resizeRect, newRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictResize_Should_ChangeResize_When_NewPositionIsInsideMinRect()
{
	QRectF newRect(50, 50, 450, 450);
	QRectF currentRect(-50, -50, 550, 550);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictResize(newRect, currentRect, minRect);

	QCOMPARE(resizeRect, minRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictMove_Should_ChangeMove_When_NewPositionAndSizeWithinMinRect()
{
	QRectF newRect(50, 50, 500, 500);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, minRect);

	QCOMPARE(resizeRect, minRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictMove_Should_NotChangeMove_When_NewPositionOutsideMinRect()
{
	QRectF newRect(-50, -50, 200, 200);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, minRect);

	QCOMPARE(resizeRect, newRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictMove_Should_ChangeMove_When_NewPositionInsideMinRect()
{
	QRectF newRect(50, 50, 500, 500);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, minRect);

	QCOMPARE(resizeRect, minRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictMove_Should_NotChangeMove_When_NewSizeOutsideMinRect()
{
	QRectF newRect(300, 300, 300, 300);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, minRect);

	QCOMPARE(resizeRect, newRect);
}

void ModifyCanvasSelectionRestrictorTest::TestRestrictMove_Should_ChangeMove_When_NewSizeInsideMinRect()
{
	QRectF newRect(300, 300, 500, 500);
	QRectF minRect(0, 0, 500, 500);
	ModifyCanvasSelectionRestrictor restrictor;

	auto resizeRect = restrictor.restrictMove(newRect, minRect);

	QCOMPARE(resizeRect, minRect);
}

QTEST_MAIN(ModifyCanvasSelectionRestrictorTest);

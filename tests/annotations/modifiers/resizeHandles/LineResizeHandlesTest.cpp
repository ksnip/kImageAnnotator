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

#include "LineResizeHandlesTest.h"

void LineResizeHandlesTest::TestInitHandles_Should_PositionTwoHandles()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);

	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	QCOMPARE(lineResizeHandles.handles().count(), 2);
	QCOMPARE(lineResizeHandles.handles()[0].anchor(), p1);
	QCOMPARE(lineResizeHandles.handles()[1].anchor(), p2);
}

void LineResizeHandlesTest::TestIndexOfHandleAt_Should_ReturnIndexOfHandle_When_HandleIsAtProvidedPosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto resultP1 = lineResizeHandles.indexOfHandleAt(p1 + QPointF(2, 2));
	auto resultP2 = lineResizeHandles.indexOfHandleAt(p2 + QPointF(-2, -2));

	QCOMPARE(lineResizeHandles.handles().count(), 2);
	QCOMPARE(resultP1, 0);
	QCOMPARE(resultP2, 1);
}

void LineResizeHandlesTest::TestIndexOfHandleAt_Should_NotReturnAnyIndex_When_HandleIsNotAtProvidedPosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto resultP1 = lineResizeHandles.indexOfHandleAt(QPointF(50, 50));

	QCOMPARE(lineResizeHandles.handles().count(), 2);
	QCOMPARE(resultP1, -1);
}

void LineResizeHandlesTest::TestHandle_Should_ReturnRectAtIndex_When_HandleAtIndexExists()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto result = lineResizeHandles.handle(1);

	QVERIFY(result != QRectF());
	QCOMPARE(result.anchor(), p2);
}

void LineResizeHandlesTest::TestHandle_Should_NotReturnRect_When_HandleAtIndexDoesntExists()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto result = lineResizeHandles.handle(3);

	QCOMPARE(result, ResizeHandle());
}

void LineResizeHandlesTest::TestGetCursorForHandle_Should_NotReturnDefaultCursor_When_ProvidedPositionOnHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto result = lineResizeHandles.cursorForPos(p1);

	QVERIFY(result != CursorHelper::defaultCursor());
}

void LineResizeHandlesTest::TestGetCursorForHandle_Should_ReturnDefaultCursor_When_ProvidedPositionNotOnHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	QPointF p3(50, 50);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);

	auto result = lineResizeHandles.cursorForPos(p3);

	QCOMPARE(result, CursorHelper::defaultCursor());
}

void LineResizeHandlesTest::TestUpdate_Should_SetMoveHandlesToNewPositions()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	QPointF p3(50, 50);
	QPointF p4(60, 60);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	LineResizeHandles lineResizeHandles(&lineItem, 1.0);
	QCOMPARE(lineResizeHandles.handles()[0].center(), p1);
	QCOMPARE(lineResizeHandles.handles()[1].center(), p2);
	lineItem.setPointAt(p3, 0);
	lineItem.setPointAt(p4, 1);

	lineResizeHandles.update();

	QCOMPARE(lineResizeHandles.handles()[0].center(), p3);
	QCOMPARE(lineResizeHandles.handles()[1].center(), p4);
}

QTEST_MAIN(LineResizeHandlesTest);

/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "PointerRectResizeHandlesTest.h"

void PointerRectResizeHandlesTest::TestInitHandles_Should_PositionPointerHandle_When_PointerRectItemProvided()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);

	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	QCOMPARE(resizeHandles.handles()[8].anchor(), pointerPosition);
}

void PointerRectResizeHandlesTest::TestIndexOfHandleAt_Should_ReturnIndexOfPointerHandle_When_HandleIsAtProvidedPosition()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.indexOfHandleAt(pointerPosition + QPointF(2, 2));

	QCOMPARE(resizeHandles.handles().count(), 9);
	QCOMPARE(result, 8);
}

void PointerRectResizeHandlesTest::TestIndexOfHandleAt_Should_NotReturnAnyIndex_When_HandleIsNotAtProvidedPosition()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.indexOfHandleAt(QPointF(100, 100));

	QCOMPARE(resizeHandles.handles().count(), 9);
	QCOMPARE(result, -1);
}

void PointerRectResizeHandlesTest::TestHandle_Should_ReturnPointerRectAtIndex_When_HandleAtIndexExists()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.handle(8);

	QVERIFY(result != QRectF());
	QCOMPARE(result.anchor(), pointerPosition);
}

void PointerRectResizeHandlesTest::TestHandle_Should_NotReturnRect_When_HandleAtIndexDoesntExists()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.handle(10);

	QCOMPARE(result, ResizeHandle());
}

void PointerRectResizeHandlesTest::TestGetCursorForHandle_Should_NotReturnDefaultCursor_When_ProvidedPositionOnHandle()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.cursorForPos(pointerPosition);

	QVERIFY(result != CursorHelper::defaultCursor());
}

void PointerRectResizeHandlesTest::TestGetCursorForHandle_Should_ReturnDefaultCursor_When_ProvidedPositionNotOnHandle()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);

	auto result = resizeHandles.cursorForPos(QPointF(100,100));

	QCOMPARE(result, CursorHelper::defaultCursor());
}

void PointerRectResizeHandlesTest::TestUpdate_Should_MovePointerHandlesToNewPosition()
{
	auto properties = TextPropertiesPtr(new AnnotationTextProperties(Qt::red, 4));
	QPointF startPosition(10,10);
	QPointF pointerPosition(50,50);
	QPointF newPointerPosition(80,80);
	AnnotationNumberPointer rectItem(startPosition, properties);
	rectItem.addPoint(pointerPosition, false);
	PointerRectResizeHandles resizeHandles(&rectItem, 1.0);
	QCOMPARE(resizeHandles.handles()[8].anchor(), pointerPosition);
	rectItem.addPoint(newPointerPosition, false);

	resizeHandles.update();

	QCOMPARE(resizeHandles.handles()[8].anchor(), newPointerPosition);
}

TEST_MAIN(PointerRectResizeHandlesTest)

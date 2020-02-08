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

#include "AnnotationItemResizerTest.h"

void AnnotationItemResizerTest::TestGrabHandle_Should_GrabHandle_When_ProvidedPointIsAtHandlePosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	AnnotationItemResizer itemResizer(&lineItem);

	itemResizer.grabHandle(p1 + QPointF(2, 2));

	auto isResizing = itemResizer.isResizing();
	QCOMPARE(isResizing, true);
}

void AnnotationItemResizerTest::TestGrabHandle_Should_NotGrabHandle_When_ProvidedPointIsNotAtHandlePosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	AnnotationItemResizer itemResizer(&lineItem);

	itemResizer.grabHandle(QPointF(0, 0));

	auto isResizing = itemResizer.isResizing();
	QCOMPARE(isResizing, false);
}

void AnnotationItemResizerTest::TestGrabHandle_Should_MoveResizeHandle_When_HandleGrabbed()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	QPointF p3(30, 30);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	AnnotationItemResizer itemResizer(&lineItem);
	QUndoStack undoStack;
	connect(&itemResizer, &AnnotationItemResizer::newCommand, &undoStack, &QUndoStack::push);

	itemResizer.grabHandle(p1);
	itemResizer.moveHandle(p3);

	QCOMPARE(lineItem.line().p1(), p3);
}

void AnnotationItemResizerTest::TestReleaseHandle_Should_ReleaseHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	AnnotationItemResizer itemResizer(&lineItem);
	itemResizer.grabHandle(p1);
	QCOMPARE(itemResizer.isResizing(), true);

	itemResizer.releaseHandle();

	QCOMPARE(itemResizer.isResizing(), false);
}

void AnnotationItemResizerTest::TestIsItemVisible_Should_ReturnFalse_When_ItemIsHidden()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	AnnotationLine lineItem(p1, properties);
	lineItem.addPoint(p2, false);
	AnnotationItemResizer itemResizer(&lineItem);
	lineItem.hide();

	auto result = itemResizer.isItemVisible();

	QCOMPARE(result, false);
}

QTEST_MAIN(AnnotationItemResizerTest);

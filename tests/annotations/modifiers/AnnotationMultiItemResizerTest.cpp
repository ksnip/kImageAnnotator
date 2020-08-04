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

#include "AnnotationMultiItemResizerTest.h"

#include "tests/mocks/MockCamera.h"

void AnnotationMultiItemResizerTest::TestGrabHandle_Should_GrabHandle_When_ProvidedPointIsAtHandlePosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);

	itemResizer.grabHandle(line1.p1());

	QCOMPARE(itemResizer.isResizing(), true);
}

void AnnotationMultiItemResizerTest::TestGrabHandle_Should_NotGrabHandle_When_ProvidedPointIsNotAtHandlePosition()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);

	itemResizer.grabHandle(line1.p1() + QPointF(-10, -10));

	QCOMPARE(itemResizer.isResizing(), false);
}

void AnnotationMultiItemResizerTest::TestGrabHandle_Should_MoveResizeHandle_When_HandleGrabbed()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	QPointF newPoint(30, 30);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	QUndoStack undoStack;
	connect(&itemResizer, &AnnotationMultiItemResizer::newCommand, &undoStack, &QUndoStack::push);
	itemResizer.attachTo(items);

	itemResizer.grabHandle(line1.p1());
	itemResizer.moveHandle(newPoint);

	QCOMPARE(item1.line().p1(), newPoint);
}

void AnnotationMultiItemResizerTest::TestGrabHandle_Should_OnlyMoveOneResizeHandle_When_MultipleItemsInList()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	QPointF newPoint(30, 30);
	AnnotationLine item1(line1.p1(), properties1);
	AnnotationLine item2(line1.p1(), properties2);
	item1.addPoint(line1.p2(), false);
	item2.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1, &item2 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	QUndoStack undoStack;
	connect(&itemResizer, &AnnotationMultiItemResizer::newCommand, &undoStack, &QUndoStack::push);
	itemResizer.attachTo(items);

	itemResizer.grabHandle(line1.p1());
	itemResizer.moveHandle(newPoint);

	QCOMPARE(item1.line().p1(), newPoint);
	QCOMPARE(item1.line().p2(), line1.p2());
	QCOMPARE(item2.line().p1(), line1.p1());
	QCOMPARE(item2.line().p2(), line1.p2());
}

void AnnotationMultiItemResizerTest::TestReleaseHandle_Should_ReleaseHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);
	itemResizer.grabHandle(line1.p1());
	QCOMPARE(itemResizer.isResizing(), true);

	itemResizer.releaseHandle();

	QCOMPARE(itemResizer.isResizing(), false);
}

void AnnotationMultiItemResizerTest::TestHasItemsAttached_Should_ReturnFalse_When_NoItemsInList()
{
	QList<AbstractAnnotationItem *> items;
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);

	auto result = itemResizer.hasItemsAttached();

	QCOMPARE(result, false);
}

void AnnotationMultiItemResizerTest::TestHasItemsAttached_Should_ReturnTrue_When_ItemsInList()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);

	auto result = itemResizer.hasItemsAttached();

	QCOMPARE(result, true);
}

void AnnotationMultiItemResizerTest::TestUpdate_Should_HideResizers_When_ItemsOfResizersNotVisible()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line1(10, 10, 20, 20);
	AnnotationLine item1(line1.p1(), properties);
	item1.addPoint(line1.p2(), false);
	QList<AbstractAnnotationItem *> items = { &item1 };
	MockCamera camera;
	AnnotationMultiItemResizer itemResizer(&camera);
	itemResizer.attachTo(items);
	QCOMPARE(itemResizer.hasItemsAttached(), true);
	item1.hide();

	itemResizer.update();

	QCOMPARE(itemResizer.hasItemsAttached(), false);
}

QTEST_MAIN(AnnotationMultiItemResizerTest);

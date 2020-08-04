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

#include "AnnotationItemModifierTest.h"

#include "tests/mocks/MockCamera.h"

void AnnotationItemModifierTest::TestHandleMousePressMoveRelease_Should_MoveResizerHandle_When_ClickedOnResizerHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(10, 20);
	QPointF p3(30, 30);
	AnnotationLine line(p1, properties);
	line.addPoint(p2, false);
	QList<AbstractAnnotationItem *> items;
	items.append(&line);
	MockCamera camera;
	AnnotationItemModifier modifer(&camera);
	QUndoStack undoStack;
	connect(&modifer, &AnnotationItemModifier::newCommand, &undoStack, &QUndoStack::push);
	modifer.handleMousePress(p1, &items, false);
	modifer.handleMouseRelease(&items);

	modifer.handleMousePress(p1, &items, false);
	modifer.handleMouseMove(p3);

	QCOMPARE(line.line().p1(), p3);
	QCOMPARE(line.line().p2(), p2);
}

void AnnotationItemModifierTest::TestHandleMousePressMove_Should_NotMoveResizerHandle_When_NotClickedOnResizerHandle()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(10, 20);
	QPointF p3(30, 30);
	QPointF p4(40, 40);
	AnnotationLine line(p1, properties);
	line.addPoint(p2, false);
	QList<AbstractAnnotationItem *> items;
	items.append(&line);
	MockCamera camera;
	AnnotationItemModifier modifer(&camera);
	modifer.handleMousePress(p1, &items, false);
	modifer.handleMouseRelease(&items);

	modifer.handleMousePress(p3, &items, false);
	modifer.handleMouseMove(p4);

	QCOMPARE(line.line().p1(), p1);
	QCOMPARE(line.line().p2(), p2);
}

void AnnotationItemModifierTest::TestHandleMousePressMoveRelease_Should_SelectMultipleItems_When_ClickedNotOnItem()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(10, 20);
	QPointF p3(15, 15);
	QPointF p4(20, 20);
	AnnotationLine line1(p1, properties1);
	AnnotationLine line2(p3, properties2);
	line1.addPoint(p2, false);
	line2.addPoint(p4, false);
	QList<AbstractAnnotationItem *> items;
	items.append(&line1);
	items.append(&line2);
	MockCamera camera;
	AnnotationItemModifier modifer(&camera);

	modifer.handleMousePress(p1 + QPointF(-5, -5), &items, false);
	modifer.handleMouseMove(p4 + QPointF(5, 5));
	modifer.handleMouseRelease(&items);

	auto results = modifer.selectedItems();
	QCOMPARE(results.count(), 2);
	QCOMPARE(results.contains(&line1), true);
	QCOMPARE(results.contains(&line2), true);
}

void AnnotationItemModifierTest::TestHandleMousePressMove_Should_MoveClickedItem_When_ClickedOnItemAndMoved()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	QPointF clickPos(15, 15);
	QPointF movePos(30, 30);
	AnnotationLine line(p1, properties);
	line.addPoint(p2, false);
	QList<AbstractAnnotationItem *> items;
	items.append(&line);
	MockCamera camera;
	AnnotationItemModifier modifer(&camera);
	QUndoStack undoStack;
	connect(&modifer, &AnnotationItemModifier::newCommand, &undoStack, &QUndoStack::push);

	modifer.handleMousePress(clickPos, &items, false);
	modifer.handleMouseMove(movePos);

	QCOMPARE(line.boundingRect().topLeft(), movePos - (clickPos - p1));
}

void AnnotationItemModifierTest::TestHandleMousePressMove_Should_MoveSelectedItems_When_ClickedOnOfSelectedItemsAndMoved()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF p1(10, 10);
	QPointF p2(30, 30);
	QPointF p3(45, 45);
	QPointF p4(60, 60);
	QPointF clickPos(20, 20);
	QPointF movePos(80, 80);
	AnnotationLine line1(p1, properties1);
	AnnotationLine line2(p3, properties2);
	line1.addPoint(p2, false);
	line2.addPoint(p4, false);
	QList<AbstractAnnotationItem *> items;
	items.append(&line1);
	items.append(&line2);
	MockCamera camera;
	AnnotationItemModifier modifer(&camera);
	QUndoStack undoStack;
	connect(&modifer, &AnnotationItemModifier::newCommand, &undoStack, &QUndoStack::push);
	modifer.handleMousePress(p1 + QPointF(-5, -5), &items, false);
	modifer.handleMouseMove(p4 + QPointF(5, 5));
	modifer.handleMouseRelease(&items);
	QCOMPARE(modifer.selectedItems().count(), 2);

	modifer.handleMousePress(clickPos, &items, false);
	modifer.handleMouseMove(movePos);

	QCOMPARE(line1.boundingRect().topLeft(), movePos - (clickPos - p1));
	QCOMPARE(line2.boundingRect().topLeft(), movePos - (clickPos - p3));
}

QTEST_MAIN(AnnotationItemModifierTest);

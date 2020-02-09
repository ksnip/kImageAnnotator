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


#include "ArrangeCommandTest.h"

void ArrangeCommandTest::TestRedo_Should_SwapItemPosition()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF pos(10, 10);
	AnnotationLine item1(pos, properties1);
	AnnotationLine item2(pos, properties2);
	item1.setZValue(1);
	item2.setZValue(2);
	QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> itemToSwap;
	itemToSwap.append(qMakePair(&item1, &item2));
	QList<AbstractAnnotationItem *> emptyItemList;
	ArrangeCommand arrangeCommand(itemToSwap, &emptyItemList);
	QCOMPARE((int) item1.zValue(), 1);
	QCOMPARE((int) item2.zValue(), 2);

	arrangeCommand.redo();

	QCOMPARE((int) item1.zValue(), 2);
	QCOMPARE((int) item2.zValue(), 1);
}

void ArrangeCommandTest::TestRedo_Should_SortItemByZValue()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties3= PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF pos(10, 10);
	AnnotationLine item1(pos, properties1);
	AnnotationLine item2(pos, properties2);
	AnnotationLine item3(pos, properties3);
	item1.setZValue(1);
	item2.setZValue(2);
	item3.setZValue(3);
	QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> emptySwapList;
	QList<AbstractAnnotationItem *> allItems;
	allItems.append(&item2);
	allItems.append(&item1);
	allItems.append(&item3);
	ArrangeCommand arrangeCommand(emptySwapList, &allItems);
	QCOMPARE((int) allItems[0]->zValue(), 2);
	QCOMPARE((int) allItems[1]->zValue(), 1);
	QCOMPARE((int) allItems[2]->zValue(), 3);

	arrangeCommand.redo();

	QCOMPARE((int) allItems[0]->zValue(), 3);
	QCOMPARE((int) allItems[1]->zValue(), 2);
	QCOMPARE((int) allItems[2]->zValue(), 1);
}

void ArrangeCommandTest::TestUndo_Should_SwapItemPositionBack()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF pos(10, 10);
	AnnotationLine item1(pos, properties1);
	AnnotationLine item2(pos, properties2);
	item1.setZValue(1);
	item2.setZValue(2);
	QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> itemToSwap;
	itemToSwap.append(qMakePair(&item1, &item2));
	QList<AbstractAnnotationItem *> emptyItemList;
	ArrangeCommand arrangeCommand(itemToSwap, &emptyItemList);
	arrangeCommand.redo();
	QCOMPARE((int) item1.zValue(), 2);
	QCOMPARE((int) item2.zValue(), 1);

	arrangeCommand.redo();

	QCOMPARE((int) item1.zValue(), 1);
	QCOMPARE((int) item2.zValue(), 2);
}

void ArrangeCommandTest::TestUndo_Should_SortItemByZValue()
{
	auto properties1 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties2 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto properties3 = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QPointF pos(10, 10);
	AnnotationLine item1(pos, properties1);
	AnnotationLine item2(pos, properties2);
	AnnotationLine item3(pos, properties3);
	item1.setZValue(1);
	item2.setZValue(2);
	item3.setZValue(3);
	QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> emptySwapList;
	QList<AbstractAnnotationItem *> allItems;
	allItems.append(&item2);
	allItems.append(&item1);
	allItems.append(&item3);
	ArrangeCommand arrangeCommand(emptySwapList, &allItems);
	QCOMPARE((int) allItems[0]->zValue(), 2);
	QCOMPARE((int) allItems[1]->zValue(), 1);
	QCOMPARE((int) allItems[2]->zValue(), 3);

	arrangeCommand.undo();

	QCOMPARE((int) allItems[0]->zValue(), 3);
	QCOMPARE((int) allItems[1]->zValue(), 2);
	QCOMPARE((int) allItems[2]->zValue(), 1);
}

QTEST_MAIN(ArrangeCommandTest);

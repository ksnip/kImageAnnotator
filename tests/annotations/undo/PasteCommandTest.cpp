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


#include "PasteCommandTest.h"

void PasteCommandTest::TestRedo_Should_AddPastedItemsToAnnotationAreaAtGivenPosition()
{
	auto offset = QPointF(10, 10);
	auto position = QPointF(50, 50);
	AnnotationArea annotationArea(new Config);
	auto properties = new AnnotationProperties(Qt::red, 1);
	QLineF line(10, 10, 20, 20);
	auto item = new AnnotationLine(line.p1(), properties);
	item->addPoint(line.p2());
	QHash<AbstractAnnotationItem *, QPointF> itemsWithOffset;
	itemsWithOffset[item] = offset;
	PasteCommand pasteCommand(itemsWithOffset, position, &annotationArea);
	QVERIFY(dynamic_cast<AnnotationLine *>(annotationArea.items().last()) == nullptr);

	pasteCommand.redo();

	auto lastItem = dynamic_cast<AnnotationLine *>(annotationArea.items().last());
	QVERIFY(lastItem != nullptr);
	QCOMPARE(lastItem->position(), position + offset);
}

void PasteCommandTest::TestUndo_Should_RemovePastedItemsFromAnnotationArea()
{
	auto offset = QPointF(10, 10);
	auto position = QPointF(50, 50);
	AnnotationArea annotationArea(new Config);
	auto properties = new AnnotationProperties(Qt::red, 1);
	QLineF line(10, 10, 20, 20);
	auto item = new AnnotationLine(line.p1(), properties);
	item->addPoint(line.p2());
	QHash<AbstractAnnotationItem *, QPointF> itemsWithOffset;
	itemsWithOffset[item] = offset;
	PasteCommand pasteCommand(itemsWithOffset, position, &annotationArea);
	pasteCommand.redo();
	QVERIFY(dynamic_cast<AnnotationLine *>(annotationArea.items().last()) != nullptr);

	pasteCommand.undo();

	QVERIFY(dynamic_cast<AnnotationLine *>(annotationArea.items().last()) == nullptr);
}

QTEST_MAIN(PasteCommandTest);

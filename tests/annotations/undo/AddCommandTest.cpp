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

#include "AddCommandTest.h"

void AddCommandTest::TestRedo_Should_ApplyOperation()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line(10, 10, 20, 20);
	auto item = new AnnotationLine(line.p1(), properties);
	item->addPoint(line.p2(), false);
	AddCommand addCommand(item, &annotationArea);
	QCOMPARE(annotationArea.items().contains(item), false);

	addCommand.redo();

	QCOMPARE(annotationArea.items().contains(item), true);
}

void AddCommandTest::TestUndo_Should_UndoOperation()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line(10, 10, 20, 20);
	auto item = new AnnotationLine(line.p1(), properties);
	item->addPoint(line.p2(), false);
	AddCommand addCommand(item, &annotationArea);
	addCommand.redo();
	QCOMPARE(annotationArea.items().contains(item), true);

	addCommand.undo();

	QCOMPARE(annotationArea.items().contains(item), false);
}

QTEST_MAIN(AddCommandTest);

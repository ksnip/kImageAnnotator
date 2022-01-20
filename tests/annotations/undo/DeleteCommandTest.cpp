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

#include "DeleteCommandTest.h"

#include "tests/mocks/MockDefaultParameters.h"

void DeleteCommandTest::TestRedo_Should_ApplyOperation()
{
	// arrange
	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line(10, 10, 20, 20);
	AnnotationLine item(line.p1(), properties);
	item.addPoint(line.p2(), false);
	annotationArea.addAnnotationItem(&item);
	QCOMPARE(annotationArea.items().contains(&item), true);
	QList<AbstractAnnotationItem *> items = { &item };
	DeleteCommand deleteCommand(items, &annotationArea);

	// act
	deleteCommand.redo();

	// assert
	QCOMPARE(annotationArea.items().contains(&item), false);
}

void DeleteCommandTest::TestUndo_Should_UndoOperation()
{
	// arrange
	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QLineF line(10, 10, 20, 20);
	AnnotationLine item(line.p1(), properties);
	item.addPoint(line.p2(), false);
	annotationArea.addAnnotationItem(&item);
	QList<AbstractAnnotationItem *> items = { &item };
	DeleteCommand deleteCommand(items, &annotationArea);
	deleteCommand.redo();
	QCOMPARE(annotationArea.items().contains(&item), false);

	// act
	deleteCommand.undo();

	// assert
	QCOMPARE(annotationArea.items().contains(&item), true);
}

TEST_MAIN(DeleteCommandTest);

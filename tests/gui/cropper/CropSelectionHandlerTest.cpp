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


#include "CropSelectionHandlerTest.h"

void CropSelectionHandlerTest::TestSetWidth_Should_EmitSelectionChangedSignal()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &CropSelectionHandler::selectionChanged);

	selectionHandler.setWidth(30);

	QCOMPARE(spy.count(), 1);
}

void CropSelectionHandlerTest::TestSetHeight_Should_EmitSelectionChangedSignal()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &CropSelectionHandler::selectionChanged);

	selectionHandler.setHeight(30);

	QCOMPARE(spy.count(), 1);
}

void CropSelectionHandlerTest::TestSetPositionX_Should_EmitSelectionChangedSignal()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &CropSelectionHandler::selectionChanged);

	selectionHandler.setPositionY(30);

	QCOMPARE(spy.count(), 1);
}

void CropSelectionHandlerTest::TestSetPositionY_Should_EmitSelectionChangedSignal()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &CropSelectionHandler::selectionChanged);

	selectionHandler.setPositionX(30);

	QCOMPARE(spy.count(), 1);
}

void CropSelectionHandlerTest::TestResetSelection_Should_SetSelectionToSceneRect()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto sceneRect = QRectF(0, 0, 500, 500);
	annotationArea.setSceneRect(sceneRect);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	selectionHandler.setWidth(400);
	QVERIFY(selectionHandler.selection() != sceneRect);

	selectionHandler.resetSelection();

	QCOMPARE(selectionHandler.selection(), sceneRect);
}

void CropSelectionHandlerTest::TestIsInMotion_Should_ReturnTrue_WhenClickedOnSelection()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(150, 150);
	annotationArea.setSceneRect(sceneRect);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, true);
}

void CropSelectionHandlerTest::TestIsInMotion_Should_ReturnTrue_WhenClickedOnHandle()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(2, 2);
	annotationArea.setSceneRect(sceneRect);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, true);
}

void CropSelectionHandlerTest::TestIsInMotion_Should_ReturnFalse_WhenClickedOutsideSelectionAndHandle()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(400, 400);
	annotationArea.setSceneRect(sceneRect);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);
	selectionHandler.setWidth(200);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, false);
}

void CropSelectionHandlerTest::TestSelectionHandles_Should_ReturnEightItems()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider);
	CropSelectionHandler selectionHandler;
	selectionHandler.init(&annotationArea);

	auto handles = selectionHandler.selectionHandles();

	QCOMPARE(handles.count(), 8);
}

QTEST_MAIN(CropSelectionHandlerTest);

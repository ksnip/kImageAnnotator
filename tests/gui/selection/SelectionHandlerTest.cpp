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

#include "SelectionHandlerTest.h"

void SelectionHandlerTest::TestSetWidth_Should_EmitSelectionChangedSignal()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &SelectionHandler::selectionChanged);

	selectionHandler.setWidth(30);

	QCOMPARE(spy.count(), 1);
}

void SelectionHandlerTest::TestSetHeight_Should_EmitSelectionChangedSignal()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &SelectionHandler::selectionChanged);

	selectionHandler.setHeight(30);

	QCOMPARE(spy.count(), 1);
}

void SelectionHandlerTest::TestSetPositionX_Should_EmitSelectionChangedSignal()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &SelectionHandler::selectionChanged);

	selectionHandler.setPositionY(30);

	QCOMPARE(spy.count(), 1);
}

void SelectionHandlerTest::TestSetPositionY_Should_EmitSelectionChangedSignal()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	QSignalSpy spy(&selectionHandler, &SelectionHandler::selectionChanged);

	selectionHandler.setPositionX(30);

	QCOMPARE(spy.count(), 1);
}

void SelectionHandlerTest::TestResetSelection_Should_SetSelectionToProvidedRect()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	auto sceneRect = QRectF(0, 0, 500, 500);
	annotationArea.setSceneRect(sceneRect);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.setWidth(400);
	QVERIFY(selectionHandler.selection() != sceneRect);

	selectionHandler.resetSelection(sceneRect, sceneRect);

	QCOMPARE(selectionHandler.selection(), sceneRect);
}

void SelectionHandlerTest::TestIsInMotion_Should_ReturnTrue_WhenClickedOnSelection()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(150, 150);
	annotationArea.setSceneRect(sceneRect);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.resetSelection(sceneRect, sceneRect);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, true);
}

void SelectionHandlerTest::TestIsInMotion_Should_ReturnTrue_WhenClickedOnHandle()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(2, 2);
	annotationArea.setSceneRect(sceneRect);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, true);
}

void SelectionHandlerTest::TestIsInMotion_Should_ReturnFalse_WhenClickedOutsideSelectionAndHandle()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	auto sceneRect = QRectF(0, 0, 500, 500);
	auto position = QPointF(400, 400);
	annotationArea.setSceneRect(sceneRect);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.setWidth(200);
	selectionHandler.grab(position);

	auto isInMotion = selectionHandler.isInMotion();

	QCOMPARE(isInMotion, false);
}

void SelectionHandlerTest::TestSelectionHandles_Should_ReturnEightItems()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);

	auto handles = selectionHandler.selectionHandles();

	QCOMPARE(handles.length(), 8);
}

void SelectionHandlerTest::TestRestrictResize_Should_KeepCurrentSelection_When_NewSelectionHasNegativeWidthAndRestrictionDisabled()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.setRestrictionEnabled(false);
	auto selectionBefore = selectionHandler.selection();

	selectionHandler.setWidth(-30);

	auto selectionAfter = selectionHandler.selection();
	QCOMPARE(selectionBefore, selectionAfter);
	QVERIFY(selectionAfter.width() >= 0);
}

void SelectionHandlerTest::TestRestrictResize_Should_KeepCurrentSelection_When_NewSelectionHasNegativeHeightAndRestrictionDisabled()
{
	MockDefaultParameters parameters;
	auto selectionRestrictor = new MockSelectionRestrictor();
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	SelectionHandler selectionHandler(selectionRestrictor);
	selectionHandler.init(&annotationArea);
	selectionHandler.setRestrictionEnabled(false);
	auto selectionBefore = selectionHandler.selection();

	selectionHandler.setHeight(-30);

	auto selectionAfter = selectionHandler.selection();
	QCOMPARE(selectionBefore, selectionAfter);
	QVERIFY(selectionAfter.height() >= 0.0);
}

QTEST_MAIN(SelectionHandlerTest)

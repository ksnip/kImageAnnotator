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


#include "SelectionHandlesAllTest.h"

void SelectionHandlesAllTest::TestIsHandleGrabbed_Should_ReturnTrue_When_ClickedOnHandle()
{
	QRectF selection(0, 0, 500, 500);
	auto halfHandle = ResizeHandleSize / 2;
	QPointF position(halfHandle, halfHandle);
	SelectionHandlesAll handles;
	handles.updateHandles(selection);
	handles.grabHandle(position, selection);

	auto isHandleGrabbed = handles.isHandleGrabbed();

	QCOMPARE(isHandleGrabbed, true);
}

void SelectionHandlesAllTest::TestIsHandleGrabbed_Should_ReturnFalse_When_ClickedOutsideHandle()
{
	QRectF selection(0, 0, 500, 500);
	QPointF position(300, 300);
	SelectionHandlesAll handles;
	handles.updateHandles(selection);
	handles.grabHandle(position, selection);

	auto isHandleGrabbed = handles.isHandleGrabbed();

	QCOMPARE(isHandleGrabbed, false);
}

void SelectionHandlesAllTest::TestGrabbedIndex_Should_ReturnIndexOfHandle_When_ClickedOnHandle()
{
	QRectF selection(0, 0, 500, 500);
	auto halfHandle = ResizeHandleSize / 2;
	QPointF position(halfHandle, halfHandle);
	SelectionHandlesAll handles;
	handles.updateHandles(selection);
	handles.grabHandle(position, selection);

	auto grabbedIndex = handles.grabbedIndex();

	QCOMPARE(grabbedIndex, 0);
}

void SelectionHandlesAllTest::TestGrabbedIndex_Should_ReturnMinusOne_When_ClickedOutsideHandle()
{
	QRectF selection(0, 0, 500, 500);
	QPointF position(300, 300);
	SelectionHandlesAll handles;
	handles.updateHandles(selection);
	handles.grabHandle(position, selection);

	auto grabbedIndex = handles.grabbedIndex();

	QCOMPARE(grabbedIndex, -1);
}

void SelectionHandlesAllTest::TestGrabOffset_Should_ReturnClickOffsetForHandle()
{
	QRectF selection(0, 0, 500, 500);
	auto halfHandle = ResizeHandleSize / 2;
	QPointF position(halfHandle, halfHandle);
	SelectionHandlesAll handles;
	handles.updateHandles(selection);
	handles.grabHandle(position, selection);

	auto grabOffset = handles.grabOffset();

	QCOMPARE(grabOffset, QPointF(halfHandle, halfHandle));
}

void SelectionHandlesAllTest::TestUpdateHandles_Should_PositionHandlesOnCorrectPlaces()
{
	QRectF selection(0, 0, 500, 500);
	SelectionHandlesAll selectionHandles;

	selectionHandles.updateHandles(selection);

	auto handles = selectionHandles.handles();

	QCOMPARE(handles[0].topLeft(), QPointF(0, 0));
	QCOMPARE(handles[1].topLeft(), QPointF(selection.width() / 2 - ResizeHandleSize / 2, 0));
	QCOMPARE(handles[2].topLeft(), QPointF(selection.width() - ResizeHandleSize, 0));
	QCOMPARE(handles[3].topLeft(), QPointF(selection.width() - ResizeHandleSize, selection.height() / 2 - ResizeHandleSize / 2));
	QCOMPARE(handles[4].topLeft(), QPointF(selection.width() - ResizeHandleSize, selection.height() - ResizeHandleSize));
	QCOMPARE(handles[5].topLeft(), QPointF(selection.width() / 2 - ResizeHandleSize / 2, selection.height() - ResizeHandleSize));
	QCOMPARE(handles[6].topLeft(), QPointF(0, selection.height() - ResizeHandleSize));
	QCOMPARE(handles[7].topLeft(), QPointF(0, selection.height() / 2 - ResizeHandleSize / 2));
}

TEST_MAIN(SelectionHandlesAllTest);

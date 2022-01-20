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

#ifndef KIMAGEANNOTATOR_RECTRESIZEHANDLESTEST_H
#define KIMAGEANNOTATOR_RECTRESIZEHANDLESTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/annotations/modifiers/resizeHandles/RectResizeHandles.h"
#include "src/annotations/items/AnnotationRect.h"
#include "src/common/helper/CursorHelper.h"

using kImageAnnotator::RectResizeHandles;
using kImageAnnotator::AnnotationRect;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::AbstractAnnotationItem;
using kImageAnnotator::CursorHelper;
using kImageAnnotator::ShapeHelper;
using kImageAnnotator::ResizeHandle;
using kImageAnnotator::PropertiesPtr;

class RectResizeHandlesTest : public QObject
{
Q_OBJECT
private slots:
	void TestInitHandles_Should_PositionEightHandles_When_RectItemProvided();
	void TestIndexOfHandleAt_Should_ReturnIndexOfHandle_When_HandleIsAtProvidedPosition();
	void TestIndexOfHandleAt_Should_NotReturnAnyIndex_When_HandleIsNotAtProvidedPosition();
	void TestHandle_Should_ReturnRectAtIndex_When_HandleAtIndexExists();
	void TestHandle_Should_NotReturnRect_When_HandleAtIndexDoesntExists();
	void TestGetCursorForHandle_Should_NotReturnDefaultCursor_When_ProvidedPositionOnHandle();
	void TestGetCursorForHandle_Should_ReturnDefaultCursor_When_ProvidedPositionNotOnHandle();
	void TestUpdate_Should_MoveHandlesToNewPosition();
};

#endif // KIMAGEANNOTATOR_RECTRESIZEHANDLESTEST_H

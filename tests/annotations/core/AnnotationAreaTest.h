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

#ifndef KIMAGEANNOTATOR_ANNOTATIONAREATEST_H
#define KIMAGEANNOTATOR_ANNOTATIONAREATEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/annotations/items/AnnotationLine.h"
#include "src/annotations/modifiers/resizeHandles/ResizeHandle.h"
#include "tests/mocks/MockDefaultParameters.h"

using kImageAnnotator::AnnotationArea;
using kImageAnnotator::AnnotationLine;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::Config;
using kImageAnnotator::PropertiesPtr;
using kImageAnnotator::ResizeHandle;
using kImageAnnotator::AnnotationItemClipboard;

class AnnotationAreaTest : public QObject
{
Q_OBJECT
private slots:
	void ExportAsImage_Should_ExportImage_When_ImageSet();
	void ExportAsImage_Should_ExportEmptyImage_When_NoImageSet();
	void ExportAsImage_Should_ExportUnscaledImage_When_ScalingEnabled();
	void AddAnnotationItem_Should_AddAnnotationItemToScene();
	void RemoveAnnotationItem_Should_RemoveAnnotationItemFromScene();
	void CanvasRect_Should_ReturnRectUnionOfAllItems_When_NoCanvasRectSet();
	void CanvasRect_Should_ReturnUserDefinedRect_When_CanvasRectSet();
};

#endif // KIMAGEANNOTATOR_ANNOTATIONAREATEST_H

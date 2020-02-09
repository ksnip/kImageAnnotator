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

#include "src/annotations/core/AnnotationArea.h"
#include "src/annotations/items/AnnotationLine.h"
#include "src/gui/annotator/AnnotationSettings.h"

using kImageAnnotator::AnnotationArea;
using kImageAnnotator::AnnotationLine;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::Config;
using kImageAnnotator::AnnotationSettings;
using kImageAnnotator::PropertiesPtr;

class AnnotationAreaTest : public QObject
{
Q_OBJECT

private slots:
	void TestExportAsImage_Should_ExportImage_When_ImageSet();
	void TestExportAsImage_Should_ExportEmptyImage_When_NoImageSet();
	void TestAddAnnotationItem_Should_AddAnnotationItemToScene();
	void TestRemoveAnnotationItem_Should_RemoveAnnotationItemFromScene();
};

#endif // KIMAGEANNOTATOR_ANNOTATIONAREATEST_H



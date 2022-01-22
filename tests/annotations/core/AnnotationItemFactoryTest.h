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

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMFACTORYTEST_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMFACTORYTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/annotations/core/AnnotationItemFactory.h"
#include "tests/mocks/MockSettingsProvider.h"
#include "tests/mocks/MockDefaultParameters.h"

using kImageAnnotator::AnnotationItemFactory;
using kImageAnnotator::AnnotationLine;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::AnnotationArrow;
using kImageAnnotator::AnnotationRect;
using kImageAnnotator::AnnotationNumber;
using kImageAnnotator::AnnotationEllipse;
using kImageAnnotator::AnnotationImage;
using kImageAnnotator::AnnotationSticker;
using kImageAnnotator::AnnotationNumberPointer;
using kImageAnnotator::Tools;
using kImageAnnotator::Config;
using kImageAnnotator::AnnotationPropertiesFactory;

class AnnotationItemFactoryTest : public QObject
{
Q_OBJECT

private slots:
	void TestCreate_Should_CreateItemAtProvidedPosition();
	void TestCreate_Should_CreateImageItemAtProvidedPosition();
	void TestCreate_Should_ReturnNullPtrForUnknownType();
	void TestCreate_Should_ReturnAnnotationLine_When_TypeIsLine();
	void TestCreate_Should_ReturnAnnotationArrow_When_TypeIsArrow();
	void TestCreate_Should_ReturnAnnotationRect_When_TypeIsRect();
	void TestCreate_Should_ReturnAnnotationEllipse_When_TypeIsEllipse();
	void TestCreate_Should_ReturnAnnotationNumber_When_TypeIsNumber();
	void TestCreate_Should_ReturnAnnotationSticker_When_TypeIsSticker();
	void TestCreate_Should_ReturnAnnotationNumberPointer_When_TypeIsNumberPointer();
	void TestClone_Should_ReturnNewItemOfSameType();
	void TestClone_Should_IncrementZValueForClonedItem();

};

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMFACTORYTEST_H

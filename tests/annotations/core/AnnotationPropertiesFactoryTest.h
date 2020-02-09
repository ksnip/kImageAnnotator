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

#ifndef KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORYTEST_H
#define KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORYTEST_H

#include <QtTest>

#include "src/annotations/core/AnnotationPropertiesFactory.h"
#include "src/gui/annotator/AnnotationSettings.h"

using kImageAnnotator::AnnotationPropertiesFactory;
using kImageAnnotator::AnnotationProperties;
using kImageAnnotator::AnnotationTextProperties;
using kImageAnnotator::AnnotationPathProperties;
using kImageAnnotator::ToolTypes;
using kImageAnnotator::FillTypes;
using kImageAnnotator::Config;
using kImageAnnotator::AnnotationSettings;

class AnnotationPropertiesFactoryTest : public QObject
{
Q_OBJECT
private slots:
	void initTestCase();
	void cleanupTestCase();

	void TestCreate_Should_SetPropertiesSizeBasedOnConfiguration();
	void TestCreate_Should_SetPropertiesColorBasedOnConfiguration();
	void TestCreate_Should_SetPropertiesTextColorBasedOnConfiguration();
	void TestCreate_Should_SetPropertiesFillTypeBasedOnConfiguration();
	void TestCreate_Should_SetShadowEnabledBasedOnConfiguration();
	void TestCreate_Should_CreatePathPropertiesWhenItemPen();
	void TestCreate_Should_CreatePathPropertiesWhenItemMarker();
	void TestCreate_Should_CreateTextPropertiesWhenItemNumber();
	void TestCreate_Should_CreateTextPropertiesWhenItemText();
	void TestCreate_Should_SetSmootPathBasedOnConfiguration();
	void TestCreate_Should_SetToolFontAndFontSizeBasedOnConfiguration();
};

#endif // ANNOTATIONPROPERTIESFACTORYTEST_H

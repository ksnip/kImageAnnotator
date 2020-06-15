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

#include "AnnotationAreaTest.h"

void AnnotationAreaTest::TestExportAsImage_Should_ExportImage_When_ImageSet()
{
	QPixmap pixmap(QSize(400, 400));
	pixmap.fill(QColor(QStringLiteral("Green")));
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider, new MockDevicePixelRatioScaler);
	annotationArea.loadImage(pixmap);

	auto resultImage = annotationArea.image();

	auto expectedImage = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
	QCOMPARE(expectedImage, resultImage);
}

void AnnotationAreaTest::TestExportAsImage_Should_ExportEmptyImage_When_NoImageSet()
{
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider, new MockDevicePixelRatioScaler);

	auto resultImage = annotationArea.image();

	QCOMPARE(QImage(), resultImage);
}

void AnnotationAreaTest::TestExportAsImage_Should_ExportScaledImage_When_ScalingEnabled()
{
	auto scaleFactor = 1.5;
	QPixmap pixmap(QSize(400, 400));
	pixmap.fill(QColor(QStringLiteral("Green")));
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	auto devicePixelRatioScaler = new MockDevicePixelRatioScaler;
	devicePixelRatioScaler->setScaleFactor(scaleFactor);
	AnnotationArea annotationArea(config, settingsProvider, devicePixelRatioScaler);
	annotationArea.loadImage(pixmap);

	auto resultImage = annotationArea.image();

	auto expectedImage = pixmap.scaled(pixmap.size() * scaleFactor).toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
	QCOMPARE(resultImage, expectedImage);
}

void AnnotationAreaTest::TestAddAnnotationItem_Should_AddAnnotationItemToScene()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider, new MockDevicePixelRatioScaler);

	annotationArea.addAnnotationItem(lineItem);

	QCOMPARE(annotationArea.items().contains(lineItem), true);
}

void AnnotationAreaTest::TestRemoveAnnotationItem_Should_RemoveAnnotationItemFromScene()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	auto config = new Config;
	auto settingsProvider = new MockSettingsProvider();
	AnnotationArea annotationArea(config, settingsProvider, new MockDevicePixelRatioScaler);
	annotationArea.addAnnotationItem(lineItem);
	QCOMPARE(annotationArea.items().contains(lineItem), true);

	annotationArea.removeAnnotationItem(lineItem);

	QCOMPARE(annotationArea.items().contains(lineItem), false);
}

QTEST_MAIN(AnnotationAreaTest);

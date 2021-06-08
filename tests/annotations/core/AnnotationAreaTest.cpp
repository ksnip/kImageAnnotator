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

void AnnotationAreaTest::ExportAsImage_Should_ExportImage_When_ImageSet()
{
	QPixmap pixmap(QSize(400, 400));
	pixmap.fill(QColor(Qt::green));
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	annotationArea.loadImage(pixmap);

	auto resultImage = annotationArea.image();

	auto expectedImage = pixmap.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
	QCOMPARE(expectedImage, resultImage);
}

void AnnotationAreaTest::ExportAsImage_Should_ExportEmptyImage_When_NoImageSet()
{
	MockDefaultParameters p;
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, &p.scaler, &p.zoomValueProvider, nullptr);

	auto resultImage = annotationArea.image();

	QCOMPARE(QImage(), resultImage);
}

void AnnotationAreaTest::ExportAsImage_Should_ExportScaledImage_When_ScalingEnabled()
{
	auto scaleFactor = 1.5;
	QPixmap pixmap(QSize(400, 400));
	pixmap.fill(QColor(Qt::green));
	MockDefaultParameters p;
	p.scaler.setScaleFactor(scaleFactor);
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, &p.scaler, &p.zoomValueProvider, nullptr);
	annotationArea.loadImage(pixmap);

	auto resultImage = annotationArea.image();

	auto expectedImage = pixmap.scaled(pixmap.size() * scaleFactor).toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
	expectedImage.setDevicePixelRatio(scaleFactor);
	QCOMPARE(resultImage, expectedImage);
}

void AnnotationAreaTest::AddAnnotationItem_Should_AddAnnotationItemToScene()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	MockDefaultParameters p;
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, &p.scaler, &p.zoomValueProvider, nullptr);

	annotationArea.addAnnotationItem(lineItem);

	QCOMPARE(annotationArea.items().contains(lineItem), true);
}

void AnnotationAreaTest::RemoveAnnotationItem_Should_RemoveAnnotationItemFromScene()
{
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(20, 20);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	MockDefaultParameters p;
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, &p.scaler, &p.zoomValueProvider, nullptr);
	annotationArea.addAnnotationItem(lineItem);
	QCOMPARE(annotationArea.items().contains(lineItem), true);

	annotationArea.removeAnnotationItem(lineItem);

	QCOMPARE(annotationArea.items().contains(lineItem), false);
}

void AnnotationAreaTest::CanvasRect_Should_ReturnRectUnionOfAllItems_When_NoCanvasRectSet()
{
	QRectF backgroundImageBoundingRect(0,0,400,400);
	QPixmap pixmap(backgroundImageBoundingRect.size().toSize());
	pixmap.fill(QColor(Qt::green));
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	annotationArea.loadImage(pixmap);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(600, 600);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	annotationArea.addAnnotationItem(lineItem);
	auto defaultCanvasRect = backgroundImageBoundingRect.united(lineItem->boundingRect().toRect());

	auto canvasRect = annotationArea.canvasRect();

	QCOMPARE(canvasRect, defaultCanvasRect);
}

void AnnotationAreaTest::CanvasRect_Should_ReturnUserDefinedRect_When_CanvasRectSet()
{
	QRect backgroundImageBoundingRect(0,0,400,400);
	QPixmap pixmap(backgroundImageBoundingRect.size());
	pixmap.fill(QColor(Qt::green));
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider, nullptr);
	annotationArea.loadImage(pixmap);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 2));
	QPointF p1(10, 10);
	QPointF p2(600, 600);
	auto lineItem = new AnnotationLine(p1, properties);
	lineItem->addPoint(p2, false);
	annotationArea.addAnnotationItem(lineItem);
	auto userDefinedCanvasRect = QRectF(100, 100, 300, 300);
	annotationArea.setCanvasRect(userDefinedCanvasRect);

	auto canvasRect = annotationArea.canvasRect();

	QCOMPARE(canvasRect, userDefinedCanvasRect);
}

QTEST_MAIN(AnnotationAreaTest);

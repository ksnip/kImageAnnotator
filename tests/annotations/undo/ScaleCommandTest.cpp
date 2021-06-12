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

#include "ScaleCommandTest.h"

#include "tests/mocks/MockDefaultParameters.h"

void ScaleCommandTest::TestRedo_Should_ScaleImageToNewSize()
{
	// arrange
	auto oldSize = QSize(500, 500);
	auto newSize = QSize(250, 250);
	QPixmap pixmap(oldSize);
	QGraphicsPixmapItem image(pixmap);

	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	ScaleCommand scaleCommand(&image, newSize, &annotationArea);

	// act
	scaleCommand.redo();

	// assert
	QCOMPARE(image.boundingRect().size().toSize(), newSize);
}

void ScaleCommandTest::TestUndo_Should_ScaleImageBackToOldSize()
{
	// arrange
	auto oldSize = QSize(500, 500);
	auto newSize = QSize(250, 250);
	QPixmap pixmap(oldSize);
	QGraphicsPixmapItem image(pixmap);
	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	ScaleCommand scaleCommand(&image, newSize, &annotationArea);
	scaleCommand.redo();
	QCOMPARE(image.boundingRect().size().toSize(), newSize);

	// act
	scaleCommand.undo();

	// assert
	QCOMPARE(image.boundingRect().size().toSize(), oldSize);
}

void ScaleCommandTest::TestRedo_Should_ScaleItemsBySameFactorAsImage()
{
	// arrange
	auto oldSize = QSize(500, 500);
	auto newSize = QSize(250, 250);
	QPixmap pixmap(oldSize);
	QGraphicsPixmapItem image(pixmap);
	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto rectItem = new AnnotationRect(QPointF(0, 0), properties);
	rectItem->addPoint(QPointF(50, 50), false);
	annotationArea.addAnnotationItem(rectItem);
	ScaleCommand scaleCommand(&image, newSize, &annotationArea);

	// act
	scaleCommand.redo();

	// assert
	QCOMPARE(rectItem->boundingRect().size().toSize(), QSize(25, 25));
}

void ScaleCommandTest::TestUndo_Should_ScaleItemsBackToOriginalSize()
{
	// arrange
	auto oldSize = QSize(500, 500);
	auto newSize = QSize(250, 250);
	QPixmap pixmap(oldSize);
	QGraphicsPixmapItem image(pixmap);
	MockDefaultParameters p;
	auto scalerMock = new MockDevicePixelRatioScaler();
	AnnotationArea annotationArea(&p.config, &p.settingsProvider, scalerMock, &p.zoomValueProvider, nullptr);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	auto rectItem = new AnnotationRect(QPointF(0, 0), properties);
	rectItem->addPoint(QPointF(50, 50), false);
	annotationArea.addAnnotationItem(rectItem);
	ScaleCommand scaleCommand(&image, newSize, &annotationArea);
	scaleCommand.redo();
	QCOMPARE(rectItem->boundingRect().size().toSize(), QSize(25, 25));

	// act
	scaleCommand.undo();

	// assert
	QCOMPARE(rectItem->boundingRect().size().toSize(), QSize(50, 50));
}

QTEST_MAIN(ScaleCommandTest)

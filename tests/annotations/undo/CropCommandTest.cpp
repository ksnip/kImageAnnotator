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


#include "CropCommandTest.h"

void CropCommandTest::TestRedo_Should_CropImageAndScene()
{
	auto config = new Config;
	AnnotationSettings annotationSettings(config);
	AnnotationArea annotationArea(config, &annotationSettings);
	QPixmap image(400, 400);
	QGraphicsPixmapItem graphicsPixmapItem(image);
	QRectF cropRect(100, 100, 200, 200);
	CropCommand cropCommand(&graphicsPixmapItem, cropRect, &annotationArea);

	cropCommand.redo();

	QCOMPARE(annotationArea.sceneRect().size(), cropRect.size());
	QCOMPARE(graphicsPixmapItem.boundingRect().size(), cropRect.size());
}

void CropCommandTest::TestRedo_Should_MoveItemToNewPosition()
{
	auto config = new Config;
	AnnotationSettings annotationSettings(config);
	AnnotationArea annotationArea(config, &annotationSettings);
	QPixmap image(400, 400);
	QGraphicsPixmapItem graphicsPixmapItem(image);
	QRectF cropRect(100, 100, 200, 200);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QRectF rect(150, 150, 300, 300);
	auto item = new AnnotationRect(rect.topLeft(), properties);
	item->addPoint(rect.bottomRight());
	annotationArea.addAnnotationItem(item);
	CropCommand cropCommand(&graphicsPixmapItem, cropRect, &annotationArea);

	cropCommand.redo();

	QCOMPARE(item->position(), QPointF(50, 50));
	QCOMPARE(item->boundingRect().size(), rect.size());
}

void CropCommandTest::TestUndo_Should_RestoreOriginalImageAndSceneSize()
{
	auto config = new Config;
	AnnotationSettings annotationSettings(config);
	AnnotationArea annotationArea(config, &annotationSettings);
	QPixmap image(400, 400);
	QGraphicsPixmapItem graphicsPixmapItem(image);
	QRectF cropRect(100, 100, 200, 200);
	CropCommand cropCommand(&graphicsPixmapItem, cropRect, &annotationArea);
	cropCommand.redo();

	cropCommand.undo();

	QVERIFY(annotationArea.sceneRect().size() == image.size());
	QVERIFY(graphicsPixmapItem.boundingRect().size() == image.size());
}

void CropCommandTest::TestUndo_Should_MoveItemBackToPreviousPosition()
{
	auto config = new Config;
	AnnotationSettings annotationSettings(config);
	AnnotationArea annotationArea(config, &annotationSettings);
	QPixmap image(400, 400);
	QGraphicsPixmapItem graphicsPixmapItem(image);
	QRectF cropRect(100, 100, 200, 200);
	auto properties = PropertiesPtr(new AnnotationProperties(Qt::red, 1));
	QRectF rect(150, 150, 300, 300);
	auto item = new AnnotationRect(rect.topLeft(), properties);
	item->addPoint(rect.bottomRight());
	annotationArea.addAnnotationItem(item);
	CropCommand cropCommand(&graphicsPixmapItem, cropRect, &annotationArea);
	cropCommand.redo();

	cropCommand.undo();

	QCOMPARE(item->position(), rect.topLeft());
	QCOMPARE(item->boundingRect().size(), rect.size());
}

QTEST_MAIN(CropCommandTest);



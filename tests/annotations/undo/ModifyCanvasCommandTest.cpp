/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "ModifyCanvasCommandTest.h"

void ModifyCanvasCommandTest::Redo_Should_ModifyCanvasSizeAndColor_When_SizeAndColorChanged()
{
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider);
	QPixmap image(400, 400);
	annotationArea.loadImage(image);
	QRectF newCanvasRect(100, 100, 200, 200);
	QColor newCanvasColor(Qt::red);
	ModifyCanvasCommand modifyCanvasCommand(newCanvasRect, newCanvasColor, &annotationArea);

	modifyCanvasCommand.redo();

	QCOMPARE(annotationArea.canvasRect(), newCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), newCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), true);
}

void ModifyCanvasCommandTest::Redo_Should_OnlyModifyCanvasColor_When_OnlyColorChanged()
{
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider);
	QPixmap image(400, 400);
	annotationArea.loadImage(image);
	QColor newCanvasColor(Qt::red);
	auto originalCanvasRect = annotationArea.canvasRect();
	ModifyCanvasCommand modifyCanvasCommand(originalCanvasRect, newCanvasColor, &annotationArea);

	modifyCanvasCommand.redo();

	QCOMPARE(annotationArea.canvasRect(), originalCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), newCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), false);
}

void ModifyCanvasCommandTest::Undo_Should_RevertCanvasSizeAndColor_When_SizeAndColorChanged()
{
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider);
	QPixmap image(400, 400);
	annotationArea.loadImage(image);
	auto originalCanvasRect = annotationArea.canvasRect();
	auto originalCanvasColor = annotationArea.canvasColor();
	QRectF newCanvasRect(100, 100, 200, 200);
	QColor newCanvasColor(Qt::red);
	ModifyCanvasCommand modifyCanvasCommand(newCanvasRect, newCanvasColor, &annotationArea);
	modifyCanvasCommand.redo();
	QCOMPARE(annotationArea.canvasRect(), newCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), newCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), true);

	modifyCanvasCommand.undo();

	QCOMPARE(annotationArea.canvasRect(), originalCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), originalCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), false);
}

void ModifyCanvasCommandTest::Undo_Should_RevertOnlyColor_When_OnlyColorChanged()
{
	MockDefaultParameters parameters;
	AnnotationArea annotationArea(&parameters.config, &parameters.settingsProvider, &parameters.scaler, &parameters.zoomValueProvider);
	QPixmap image(400, 400);
	annotationArea.loadImage(image);
	QColor newCanvasColor(Qt::red);
	auto originalCanvasRect = annotationArea.canvasRect();
	auto originalCanvasColor = annotationArea.canvasColor();
	ModifyCanvasCommand modifyCanvasCommand(originalCanvasRect, newCanvasColor, &annotationArea);
	modifyCanvasCommand.redo();
	QCOMPARE(annotationArea.canvasRect(), originalCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), newCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), false);

	modifyCanvasCommand.undo();

	QCOMPARE(annotationArea.canvasRect(), originalCanvasRect);
	QCOMPARE(annotationArea.canvasColor(), originalCanvasColor);
	QCOMPARE(annotationArea.isCustomCanvasRect(), false);
}

QTEST_MAIN(ModifyCanvasCommandTest);

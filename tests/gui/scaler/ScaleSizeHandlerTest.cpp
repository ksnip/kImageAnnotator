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


#include "ScaleSizeHandlerTest.h"

void ScaleSizeHandlerTest::TestSetWidthPixel_Should_UpdatePercentCorrectly()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	QSignalSpy spy(&sizeHandler, &ScaleSizeHandler::widthPercentChanged);

	sizeHandler.setWidthPixel(250);

	QCOMPARE(spy.count(), 1);
	auto resultValue = qvariant_cast<int>(spy.at(0).at(0));
	QCOMPARE(resultValue, 50);
}

void ScaleSizeHandlerTest::TestSetHeightPixel_Should_UpdatePercentCorrectly()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	QSignalSpy spy(&sizeHandler, &ScaleSizeHandler::heightPercentChanged);

	sizeHandler.setHeightPixel(250);

	QCOMPARE(spy.count(), 1);
	auto resultValue = qvariant_cast<int>(spy.at(0).at(0));
	QCOMPARE(resultValue, 50);
}

void ScaleSizeHandlerTest::TestSetWidthPercent_Should_UpdatePixelCorrectly()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	QSignalSpy spy(&sizeHandler, &ScaleSizeHandler::widthPixelChanged);

	sizeHandler.setWidthPercent(50);

	QCOMPARE(spy.count(), 1);
	auto resultValue = qvariant_cast<int>(spy.at(0).at(0));
	QCOMPARE(resultValue, 250);
}

void ScaleSizeHandlerTest::TestSetHeightPercent_Should_UpdatePixelCorrectly()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	QSignalSpy spy(&sizeHandler, &ScaleSizeHandler::heightPixelChanged);

	sizeHandler.setHeightPercent(50);

	QCOMPARE(spy.count(), 1);
	auto resultValue = qvariant_cast<int>(spy.at(0).at(0));
	QCOMPARE(resultValue, 250);
}

void ScaleSizeHandlerTest::TestSetWidthPixel_Should_NotUpdateHeight_When_KeepAspectRatioNotSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(false);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::heightPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::heightPixelChanged);

	sizeHandler.setWidthPixel(250);

	QCOMPARE(percentSpy.count(), 0);
	QCOMPARE(pixelSpy.count(), 0);
}

void ScaleSizeHandlerTest::TestSetWidthPixel_Should_UpdateHeight_When_KeepAspectRatioIsSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(true);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::heightPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::heightPixelChanged);

	sizeHandler.setWidthPixel(250);

	QCOMPARE(percentSpy.count(), 1);
	QCOMPARE(pixelSpy.count(), 1);
	auto percent = qvariant_cast<int>(percentSpy.at(0).at(0));
	auto pixel = qvariant_cast<int>(pixelSpy.at(0).at(0));
	QCOMPARE(percent, 50);
	QCOMPARE(pixel, 250);
}

void ScaleSizeHandlerTest::TestSetWidthPercent_Should_NotUpdateHeight_When_KeepAspectRatioNotSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(false);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::heightPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::heightPixelChanged);

	sizeHandler.setWidthPercent(50);

	QCOMPARE(percentSpy.count(), 0);
	QCOMPARE(pixelSpy.count(), 0);
}

void ScaleSizeHandlerTest::TestSetWidthPercent_Should_UpdateHeight_When_KeepAspectRatioIsSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(true);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::heightPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::heightPixelChanged);

	sizeHandler.setWidthPercent(50);

	QCOMPARE(percentSpy.count(), 1);
	QCOMPARE(pixelSpy.count(), 1);
	auto percent = qvariant_cast<int>(percentSpy.at(0).at(0));
	auto pixel = qvariant_cast<int>(pixelSpy.at(0).at(0));
	QCOMPARE(percent, 50);
	QCOMPARE(pixel, 250);
}

void ScaleSizeHandlerTest::TestSetHeightPixel_Should_NotUpdateWidth_When_KeepAspectRatioNotSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(false);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::widthPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::widthPixelChanged);

	sizeHandler.setHeightPixel(250);

	QCOMPARE(percentSpy.count(), 0);
	QCOMPARE(pixelSpy.count(), 0);
}

void ScaleSizeHandlerTest::TestSetHeightPixel_Should_UpdateWidth_When_KeepAspectRatioIsSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(true);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::widthPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::widthPixelChanged);

	sizeHandler.setHeightPixel(250);

	QCOMPARE(percentSpy.count(), 1);
	QCOMPARE(pixelSpy.count(), 1);
	auto percent = qvariant_cast<int>(percentSpy.at(0).at(0));
	auto pixel = qvariant_cast<int>(pixelSpy.at(0).at(0));
	QCOMPARE(percent, 50);
	QCOMPARE(pixel, 250);
}

void ScaleSizeHandlerTest::TestSetHeightPercent_Should_NotUpdateWidth_When_KeepAspectRatioNotSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(false);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::widthPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::widthPixelChanged);

	sizeHandler.setHeightPercent(50);

	QCOMPARE(percentSpy.count(), 0);
	QCOMPARE(pixelSpy.count(), 0);
}

void ScaleSizeHandlerTest::TestSetHeightPercent_Should_UpdateWidth_When_KeepAspectRatioIsSet()
{
	QSize size(500, 500);
	ScaleSizeHandler sizeHandler;
	sizeHandler.setSize(size);
	sizeHandler.setAspectRatio(true);
	QSignalSpy percentSpy(&sizeHandler, &ScaleSizeHandler::widthPercentChanged);
	QSignalSpy pixelSpy(&sizeHandler, &ScaleSizeHandler::widthPixelChanged);

	sizeHandler.setHeightPercent(50);

	QCOMPARE(percentSpy.count(), 1);
	QCOMPARE(pixelSpy.count(), 1);
	auto percent = qvariant_cast<int>(percentSpy.at(0).at(0));
	auto pixel = qvariant_cast<int>(pixelSpy.at(0).at(0));
	QCOMPARE(percent, 50);
	QCOMPARE(pixel, 250);
}

TEST_MAIN(ScaleSizeHandlerTest);

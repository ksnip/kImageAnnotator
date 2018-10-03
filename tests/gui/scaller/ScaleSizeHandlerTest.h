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

#ifndef KIMAGEANNOTATOR_SCALESIZEHANDLERTEST_H
#define KIMAGEANNOTATOR_SCALESIZEHANDLERTEST_H

#include <QtTest>

#include "src/gui/scaller/ScaleSizeHandler.h"

using kImageAnnotator::ScaleSizeHandler;

class ScaleSizeHandlerTest : public QObject
{
Q_OBJECT

private slots:
	void TestSetWidthPixel_Should_UpdatePercentCorrectly();
	void TestSetHeightPixel_Should_UpdatePercentCorrectly();
	void TestSetWidthPercent_Should_UpdatePixelCorrectly();
	void TestSetHeightPercent_Should_UpdatePixelCorrectly();
	void TestSetWidthPixel_Should_NotUpdateHeight_When_KeepAspectRatioNotSet();
	void TestSetWidthPixel_Should_UpdateHeight_When_KeepAspectRatioIsSet();
	void TestSetWidthPercent_Should_NotUpdateHeight_When_KeepAspectRatioNotSet();
	void TestSetWidthPercent_Should_UpdateHeight_When_KeepAspectRatioIsSet();
	void TestSetHeightPixel_Should_NotUpdateWidth_When_KeepAspectRatioNotSet();
	void TestSetHeightPixel_Should_UpdateWidth_When_KeepAspectRatioIsSet();
	void TestSetHeightPercent_Should_NotUpdateWidth_When_KeepAspectRatioNotSet();
	void TestSetHeightPercent_Should_UpdateWidth_When_KeepAspectRatioIsSet();
};

#endif // KIMAGEANNOTATOR_SCALESIZEHANDLERTEST_H

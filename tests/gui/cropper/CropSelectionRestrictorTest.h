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

#ifndef KIMAGEANNOTATOR_CROPSELECTIONRESTRICTORTEST_H
#define KIMAGEANNOTATOR_CROPSELECTIONRESTRICTORTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/gui/cropper/CropSelectionRestrictor.h"

using kImageAnnotator::CropSelectionRestrictor;

class CropSelectionRestrictorTest : public QObject
{
Q_OBJECT
private slots:
	void TestRestrictResize_Should_NotChangeResize_When_NewSizeSmallerThenMaxRect();
	void TestRestrictResize_Should_ChangeResize_When_NewSizeLargerThenMaxRect();
	void TestRestrictResize_Should_ChangeResize_When_NewPositionIsOutsideMaxRect();
	void TestRestrictResize_Should_ChangeResize_When_NewPositionHasNegativeWidth();
	void TestRestrictResize_Should_ChangeResize_When_NewPositionHasNegativeHeight();
	void TestRestrictMove_Should_NotChangeMove_When_NewPositionAndSizeWithinMaxRect();
	void TestRestrictMove_Should_ChangeMove_When_NewPositionOutsideMaxRect();
	void TestRestrictMove_Should_ChangeMove_When_NewSizeOutsideMaxRect();
};

#endif // KIMAGEANNOTATOR_CROPSELECTIONRESTRICTORTEST_H

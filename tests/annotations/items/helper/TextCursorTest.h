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

#ifndef KIMAGEANNOTATOR_TEXTCURSORTEST_H
#define KIMAGEANNOTATOR_TEXTCURSORTEST_H

#include <QtTest>

#include "src/annotations/items/text/TextCursor.h"

using kImageAnnotator::TextCursor;
using kImageAnnotator::TextPositions;

class TextCursorTest : public QObject
{
Q_OBJECT

private slots:
	void TestMove_Should_MoveCursorByOnePointToRight_When_DirectionNext();
	void TestMove_Should_MoveCursorByOnePointToLeft_When_DirectionPrevious();
	void TestMove_Should_MoveCursorToEnd_When_DirectionPreviousAndCurrentPositionAtStart();
	void TestMove_Should_MoveCursorToStart_When_DirectionNextAndCurrentPositionAtEnd();
	void TestMove_Should_MoveCursorToNextLineSamePosition_When_DirectionDown();
	void TestMove_Should_NotMoveCursor_When_DirectionDownAndInLastLine();
	void TestMove_Should_NotMoveCursor_When_DirectionUpAndInFirstLine();
	void TestMove_Should_MoveCursorToPreviousLineSamePosition_When_DirectionUpAndNotInFirstLine();
	void TestMove_Should_MoveCursorToEndOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsSmaller();
	void TestMove_Should_MoveCursorToEndOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsSmaller();
	void TestMove_Should_MoveCursorToSamePositionOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsLarger();
	void TestMove_Should_MoveCursorToSamePositionOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsLarger();
	void TestMoveForwardBy_Should_MoveCursorForwardByRequestedSteps();
	void TestMoveForwardBy_Should_MoveCursorToStartPlusRemainingSteps_When_RequestedSteps_LargerThenTextLength();
};

#endif // KIMAGEANNOTATOR_TEXTCURSORTEST_H

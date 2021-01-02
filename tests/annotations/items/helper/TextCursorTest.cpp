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


#include "TextCursorTest.h"

void TextCursorTest::TestMove_Should_MoveCursorByOnePointToRight_When_DirectionNext()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    QCOMPARE(textCursor.position(), 0);

    textCursor.move(TextPositions::Next, text);

    QCOMPARE(textCursor.position(), 1);
}

void TextCursorTest::TestMove_Should_MoveCursorByOnePointToLeft_When_DirectionPrevious()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Next, text);
    QCOMPARE(textCursor.position(), 1);

    textCursor.move(TextPositions::Previous, text);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToEnd_When_DirectionPreviousAndCurrentPositionAtStart()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    QCOMPARE(textCursor.position(), 0);

    textCursor.move(TextPositions::Previous, text);

    QCOMPARE(textCursor.position(), text.length());
}

void TextCursorTest::TestMove_Should_MoveCursorToStart_When_DirectionNextAndCurrentPositionAtEnd()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Previous, text);
    QCOMPARE(textCursor.position(), text.length());

    textCursor.move(TextPositions::Next, text);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToNextLineSamePosition_When_DirectionDown()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    QCOMPARE(textCursor.position(), 0);

    textCursor.move(TextPositions::Down, text);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_NotMoveCursor_When_DirectionDownAndInLastLine()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Down, text);
    QCOMPARE(textCursor.position(), 9);

    textCursor.move(TextPositions::Down, text);

    QCOMPARE(textCursor.position(), 9);
}

void TextCursorTest::TestMove_Should_NotMoveCursor_When_DirectionUpAndInFirstLine()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    QCOMPARE(textCursor.position(), 0);

    textCursor.move(TextPositions::Up, text);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToPreviousLineSamePosition_When_DirectionUpAndNotInFirstLine()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Down, text);
    QCOMPARE(textCursor.position(), 9);

    textCursor.move(TextPositions::Up, text);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_MoveCursorToEndOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsSmaller()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    QCOMPARE(textCursor.position(), 4);

    textCursor.move(TextPositions::Down, text);

    QCOMPARE(textCursor.position(), 8);
}

void TextCursorTest::TestMove_Should_MoveCursorToEndOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsSmaller()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    QCOMPARE(textCursor.position(), 16);

    textCursor.move(TextPositions::Up, text);

    QCOMPARE(textCursor.position(), 8);
}

void TextCursorTest::TestMove_Should_MoveCursorToSamePositionOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsLarger()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    QCOMPARE(textCursor.position(), 8);

    textCursor.move(TextPositions::Up, text);

    QCOMPARE(textCursor.position(), 3);
}

void TextCursorTest::TestMove_Should_MoveCursorToSamePositionOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsLarger()
{
    TextCursor textCursor;
    QString text = QLatin1String("Test\n"
                                  "123\n"
                                  "test123");
    textCursor.move(TextPositions::Down, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    textCursor.move(TextPositions::Next, text);
    QCOMPARE(textCursor.position(), 8);

    textCursor.move(TextPositions::Down, text);

    QCOMPARE(textCursor.position(), 12);
}

void TextCursorTest::TestMoveForwardBy_Should_MoveCursorForwardByRequestedSteps()
{
	TextCursor textCursor;
	QString text = QLatin1String("Test\n"
								 "123\n"
								 "test123");
	QCOMPARE(textCursor.position(), 0);

	textCursor.moveForwardBy(text, 2);

	QCOMPARE(textCursor.position(), 2);
}

void TextCursorTest::TestMoveForwardBy_Should_MoveCursorToStartPlusRemainingSteps_When_RequestedSteps_LargerThenTextLength()
{
	TextCursor textCursor;
	QString text = QLatin1String("Test\n"
								 "123\n"
								 "test123");
	textCursor.move(TextPositions::Previous, text);
	textCursor.move(TextPositions::Previous, text);
	QCOMPARE(textCursor.position(), text.length() - 1);

	textCursor.moveForwardBy(text, 3);

	QCOMPARE(textCursor.position(), 1);
}

QTEST_MAIN(TextCursorTest);

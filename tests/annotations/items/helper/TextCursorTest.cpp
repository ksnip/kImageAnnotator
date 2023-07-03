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

void TextCursorTest::TestMove_Should_MoveCursorToBeginning_When_DirectionBeginning()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
    TextCursor textCursor(&textDocument);
    textCursor.setPosition(16);

    textCursor.movePosition(QTextCursor::Start);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToEnd_When_DirectionEnd()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);

    textCursor.movePosition(QTextCursor::End);

    QCOMPARE(textCursor.position(), 16);

}

void TextCursorTest::TestMove_Should_MoveCursorByOnePointToRight_When_DirectionNext()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);

    textCursor.movePosition(QTextCursor::Right);

    QCOMPARE(textCursor.position(), 1);
}

void TextCursorTest::TestMove_Should_MoveCursorToNextWordBeginning_When_DirectionNextAndModifierCtrl()
{
	QTextDocument textDocument(" This is  a string\n"
							   "spanning multiple lines "
							   " 123 1  ");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);
	QVector<int> nextPositionList{ 1, 6, 10, 12, 18, 19, 28, 37, 44, 48, 51, 51 };

    for(int nextPosition : nextPositionList) {
        textCursor.movePosition(QTextCursor::NextWord);

        QCOMPARE(textCursor.position(), nextPosition);
    }
}

void TextCursorTest::TestMove_Should_MoveCursorByOnePointToLeft_When_DirectionPrevious()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.movePosition(QTextCursor::Right);
    QCOMPARE(textCursor.position(), 1);

    textCursor.movePosition(QTextCursor::Left);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToPreviousWordBeginning_When_DirectionPreviousAndModifierCtrl()
{
	QTextDocument textDocument(" This is  a string\n"
							   "spanning multiple lines "
							   " 123 1  ");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(51);
    QCOMPARE(textCursor.position(), 51);
    QVector<int> prevPositionList{ 48, 44, 37, 28, 19, 18, 12, 10, 6, 1, 0, 0 };

    for(int prevPosition : prevPositionList) {
        textCursor.movePosition(QTextCursor::PreviousWord);

        QCOMPARE(textCursor.position(), prevPosition);
    }
}

void TextCursorTest::TestMove_Should_MoveCursorToStart_When_DirectionPreviousAndCurrentPositionAtStart()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);

    textCursor.movePosition(QTextCursor::Left);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToEnd_When_DirectionNextAndCurrentPositionAtEnd()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(16);

    textCursor.movePosition(QTextCursor::Right);

    QCOMPARE(textCursor.position(), 16);
}

void TextCursorTest::TestMove_Should_MoveCursorToNextLineSamePosition_When_DirectionDown()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);

    textCursor.movePosition(QTextCursor::Down);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_NotMoveCursor_When_DirectionDownAndInLastLine()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(9);

    textCursor.movePosition(QTextCursor::Down);

    QCOMPARE(textCursor.position(), 9);
}

void TextCursorTest::TestMove_Should_NotMoveCursor_When_DirectionUpAndInFirstLine()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    QCOMPARE(textCursor.position(), 0);

    textCursor.movePosition(QTextCursor::Up);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToPreviousLineSamePosition_When_DirectionUpAndNotInFirstLine()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(9);

    textCursor.movePosition(QTextCursor::Up);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_MoveCursorToEndOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsSmaller()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(4);

    textCursor.movePosition(QTextCursor::Down);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_MoveCursorToEndOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsSmaller()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(16);

    textCursor.movePosition(QTextCursor::Up);

    QCOMPARE(textCursor.position(), 5);
}

void TextCursorTest::TestMove_Should_MoveCursorToSamePositionOfPreviousLine_When_DirectionUpAndPositionAtEndOfLineAndLineAboveIsLarger()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(8);

    textCursor.movePosition(QTextCursor::Up);

    QCOMPARE(textCursor.position(), 0);
}

void TextCursorTest::TestMove_Should_MoveCursorToSamePositionOfNextLine_When_DirectionDownAndPositionAtEndOfLineAndLineBelowIsLarger()
{
	QTextDocument textDocument("Test\n"
							   "123\n"
							   "test123");
	TextCursor textCursor(&textDocument);
    textCursor.setPosition(8);

    textCursor.movePosition(QTextCursor::Down);

    QCOMPARE(textCursor.position(), 9);
}

TEST_MAIN(TextCursorTest);

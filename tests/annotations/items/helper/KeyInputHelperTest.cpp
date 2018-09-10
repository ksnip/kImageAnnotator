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


#include "KeyInputHelperTest.h"

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitRemoveSignal_When_KeyIsBackspace()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::remove);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Previous);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitRemoveSignal_When_KeyIsDelete()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::remove);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Next);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsReturn()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::insert);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultText = qvariant_cast<QString>(spy.at(0).at(0));
    QCOMPARE(resultText, QStringLiteral("\n"));
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsEnter()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::insert);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultText = qvariant_cast<QString>(spy.at(0).at(0));
    QCOMPARE(resultText, QStringLiteral("\n"));
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitEscapeSignal_When_KeyIsEscape()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::escape);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowLeft()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Previous);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowRight()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Next);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowUp()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Up);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowDown()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultDirection = qvariant_cast<int>(spy.at(0).at(0));
    QCOMPARE(resultDirection, (int) TextPositions::Down);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitPasteSignal_When_KeyIsPaste()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::paste);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Paste, Qt::NoModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitPasteSignal_When_KeySequenceIsPaste()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::paste);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_V, Qt::ControlModifier);

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitInsertSignal_When_KeyIsCharacter()
{
    KeyInputHelper keyInputHelper;
    QSignalSpy spy(&keyInputHelper, &KeyInputHelper::insert);
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_J, Qt::NoModifier, QStringLiteral("j"));

    keyInputHelper.handleKeyPress(&keyEvent);

    QCOMPARE(spy.count(), 1);
    auto resultText = qvariant_cast<QString>(spy.at(0).at(0));
    QCOMPARE(resultText, QStringLiteral("j"));
}

QTEST_MAIN(KeyInputHelperTest);
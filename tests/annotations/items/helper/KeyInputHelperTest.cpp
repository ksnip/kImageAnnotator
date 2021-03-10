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
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::remove);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Previous);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitRemoveSignal_When_KeyIsDelete()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::remove);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Next);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsReturnAndModifierShift()
{
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::insert);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::ShiftModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultText = qvariant_cast<QString>(spy.at(0).at(0));
	QCOMPARE(resultText, QStringLiteral("\n"));
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsEnterAndModifierShift()
{
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::insert);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::ShiftModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultText = qvariant_cast<QString>(spy.at(0).at(0));
	QCOMPARE(resultText, QStringLiteral("\n"));
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitEscape_When_KeyIsReturnAndNoModifier()
{
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::escape);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitEscape_When_KeyIsEnterAndNoModifier()
{
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::escape);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitEscapeSignal_When_KeyIsEscape()
{
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::escape);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsHome()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Home, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Beginning);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsEnd()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_End, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::End);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowLeft()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Previous);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowLeftAndModifierCtrl()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::ControlModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::PreviousWordBeginning);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowRight()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Next);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowRightAndModifierCtrl()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::ControlModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::NextWordBeginning);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowUp()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Up);
}

void KeyInputHelperTest::TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowDown()
{
	qRegisterMetaType<TextPositions>("TextPositions");
	KeyInputHelper keyInputHelper;
	QSignalSpy spy(&keyInputHelper, &KeyInputHelper::move);
	QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);

	keyInputHelper.handleKeyPress(&keyEvent);

	QCOMPARE(spy.count(), 1);
	auto resultDirection = qvariant_cast<TextPositions>(spy.at(0).at(0));
	QCOMPARE(resultDirection, TextPositions::Down);
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

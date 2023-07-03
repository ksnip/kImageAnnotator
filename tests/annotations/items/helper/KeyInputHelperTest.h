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

#ifndef KIMAGEANNOTATOR_KEYINPUTHELPERTEST_H
#define KIMAGEANNOTATOR_KEYINPUTHELPERTEST_H

#include <QtTest>

#include "tests/utils/TestRunner.h"
#include "src/annotations/items/text/KeyInputHelper.h"

using kImageAnnotator::KeyInputHelper;

class KeyInputHelperTest : public QObject
{
Q_OBJECT

private slots:
	void TestHandleKeyPress_Should_EmitRemoveSignal_When_KeyIsBackspace();
	void TestHandleKeyPress_Should_EmitRemoveSignal_When_KeyIsDelete();
	void TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsReturnAndModifierShift();
	void TestHandleKeyPress_Should_EmitInsertSignalWithNewLine_When_KeyIsEnterAndModifierShift();
	void TestHandleKeyPress_Should_EmitEscape_When_KeyIsReturnAndNoModifier();
	void TestHandleKeyPress_Should_EmitEscape_When_KeyIsEnterAndNoModifier();
	void TestHandleKeyPress_Should_EmitEscapeSignal_When_KeyIsEscape();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsHome();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsEnd();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowLeft();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowLeftAndModifierCtrl();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowRight();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowRightAndModifierCtrl();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowUp();
	void TestHandleKeyPress_Should_EmitMoveSignal_When_KeyIsArrowDown();
	void TestHandleKeyPress_Should_EmitPasteSignal_When_KeyIsPaste();
	void TestHandleKeyPress_Should_EmitPasteSignal_When_KeySequenceIsPaste();
	void TestHandleKeyPress_Should_EmitInsertSignal_When_KeyIsCharacter();
};

#endif // KIMAGEANNOTATOR_KEYINPUTHELPERTEST_H

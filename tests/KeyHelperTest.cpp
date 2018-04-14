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

#include "KeyHelperTest.h"

void KeyHelperTest::TestKeyRelease_Should_EmitSignal_When_DeleteKeyReleased()
{
    QKeyEvent keyEvent(QEvent::KeyRelease, Qt::Key_Delete, Qt::NoModifier);
    KeyHelper keyHelper;
    QSignalSpy spy(&keyHelper, &KeyHelper::deleteReleased);

    keyHelper.keyRelease(&keyEvent);

    QCOMPARE(spy.count(), 1);
}

void KeyHelperTest::TestKeyRelease_Should_EmitSignal_When_EscapeKeyReleased()
{
    QKeyEvent keyEvent(QEvent::KeyRelease, Qt::Key_Escape, Qt::NoModifier);
    KeyHelper keyHelper;
    QSignalSpy spy(&keyHelper, &KeyHelper::escapeReleased);

    keyHelper.keyRelease(&keyEvent);

    QCOMPARE(spy.count(), 1);
}

void KeyHelperTest::TestIsControlPressed_ShouldReturnTrue_When_ControlWasPressed()
{
    QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Control, Qt::NoModifier);
    KeyHelper keyHelper;
    QCOMPARE(keyHelper.isControlPressed(), false);

    keyHelper.keyPress(&keyEvent);

    QCOMPARE(keyHelper.isControlPressed(), true);
}

void KeyHelperTest::TestIsControlPressed_ShouldReturnFalse_When_ControlWasReleased()
{
    QKeyEvent keyPressEvent(QEvent::KeyPress, Qt::Key_Control, Qt::NoModifier);
    QKeyEvent keyReleaseEvent(QEvent::KeyRelease, Qt::Key_Control, Qt::NoModifier);
    KeyHelper keyHelper;
    keyHelper.keyPress(&keyPressEvent);
    QCOMPARE(keyHelper.isControlPressed(), true);

    keyHelper.keyRelease(&keyReleaseEvent);

    QCOMPARE(keyHelper.isControlPressed(), false);
}

QTEST_MAIN(KeyHelperTest);

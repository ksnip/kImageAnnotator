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

#include "KeyHelper.h"

KeyHelper::KeyHelper()
{
    mKeyToIsPressed[Qt::Key_Delete] = false;
    mKeyToIsPressed[Qt::Key_Escape] = false;
    mKeyToIsPressed[Qt::Key_Control] = false;
}

void KeyHelper::keyPress(QKeyEvent* keyEvent)
{
    auto key = static_cast<Qt::Key>(keyEvent->key());
    if(mKeyToIsPressed.contains(key)) {
        mKeyToIsPressed[key] = true;
    }
}

void KeyHelper::keyRelease(QKeyEvent* keyEvent)
{
    auto key = static_cast<Qt::Key>(keyEvent->key());
    if(mKeyToIsPressed.contains(key)) {
        mKeyToIsPressed[key] = false;
        emitReleaseSignal(key);
    }
}

bool KeyHelper::isControlPressed() const
{
    return mKeyToIsPressed[Qt::Key_Control];
}

void KeyHelper::emitReleaseSignal(Qt::Key key)
{
    if(key == Qt::Key_Delete) {
        emit deleteReleased();
    }

    if(key == Qt::Key_Escape) {
        emit escapeReleased();
    }
}

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

#include "TextCursor.h"

TextCursor::TextCursor()
{
    mBlinkTimer = new QTimer(this);

    connect(mBlinkTimer, &QTimer::timeout, [this]()
    {
        mIsVisible = !mIsVisible;
    });

    mBlinkTimer->start(mBlinkIntervalInMs);
}

TextCursor::~TextCursor()
{
    delete mBlinkTimer;
}

void TextCursor::move(TextPositions direction, const QString &text)
{
    switch (direction) {
        case TextPositions::Next:
            moveCursorForward(text);
            break;
        case TextPositions::Previous:
            moveCursorBack(text);
            break;
        case TextPositions::Up:
        case TextPositions::Down:
            QTextDocument document(text);
            auto block = document.findBlock(mPosition);
            if ((direction == TextPositions::Up && block == document.firstBlock()) || (direction == TextPositions::Down && block == document.lastBlock())) {
                break;
            }
            auto blockPos = block.position();
            if (direction == TextPositions::Up) {
                block = block.previous();
            } else {
                block = block.next();
            }
            if ((mPosition - blockPos) < block.length()) {
                mPosition = block.position() + mPosition - blockPos;
            } else {
                mPosition = block.position() + block.length() - 1;
            }
            break;
    }
    mIsVisible = true;
}

int TextCursor::position() const
{
    return mPosition;
}

void TextCursor::moveCursorForward(const QString &text)
{
    mPosition++;
    if (mPosition > text.length()) {
        mPosition = 0;
    }
}

void TextCursor::moveCursorBack(const QString &text)
{
    mPosition--;
    if (mPosition < 0) {
        mPosition = text.length();
    }
}

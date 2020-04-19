/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

namespace kImageAnnotator {

TextCursor::TextCursor()
{
    mBlinkTimer = new QTimer(this);

    connect(mBlinkTimer, &QTimer::timeout, [this]()
    {
        mIsVisible = !mIsVisible;
        emit tick();
    });
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
            moveCursorUp(text);
            break;
        case TextPositions::Down:
            moveCursorDown(text);
            break;
    }
    mIsVisible = true;
}

void TextCursor::start()
{
    mBlinkTimer->start(mBlinkIntervalInMs);
}

void TextCursor::stop()
{
    mBlinkTimer->stop();
    mIsVisible = false;
}

int TextCursor::position() const
{
    return mPosition;
}

void TextCursor::setPosition(int newPosition)
{
    mPosition = newPosition;
}

bool TextCursor::isVisible() const
{
    return mIsVisible;
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

void TextCursor::moveCursorUp(const QString &text)
{
    QTextDocument document(text);
    auto currentBlock = document.findBlock(mPosition);

    if (currentBlock == document.firstBlock()) {
        return;
    }

    auto positionInBlock = currentBlock.position();
    auto previousBlock = currentBlock.previous();

    fitPositionToNewBlock(positionInBlock, previousBlock);
}

void TextCursor::moveCursorDown(const QString &text)
{
    QTextDocument document(text);
    auto currentBlock = document.findBlock(mPosition);
    if (currentBlock == document.lastBlock()) {
        return;
    }

    auto positionInBlock = currentBlock.position();
    auto nextBlock = currentBlock.next();

    fitPositionToNewBlock(positionInBlock, nextBlock);
}

void TextCursor::fitPositionToNewBlock(int positionInBlock, const QTextBlock &targetBlock)
{
    if ((mPosition - positionInBlock) < targetBlock.length()) {
        moveToSamePositionInNewBlock(positionInBlock, targetBlock);
    } else {
        movePositionToEndOfBlock(targetBlock);
    }
}

void TextCursor::moveToSamePositionInNewBlock(int positionInBlock, const QTextBlock &targetBlock)
{
    mPosition = targetBlock.position() + mPosition - positionInBlock;
}

void TextCursor::movePositionToEndOfBlock(const QTextBlock &targetBlock)
{
    mPosition = targetBlock.position() + targetBlock.length() - 1;
}

} // namespace kImageAnnotator

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

TextCursor::TextCursor() :
	mBlinkTimer(new QTimer(this))
{
	connectSlots();
}

TextCursor::TextCursor(const TextCursor &other) :
	mBlinkTimer(new QTimer(this)),
	mPosition(other.mPosition)
{
	connectSlots();
}

TextCursor::~TextCursor()
{
    delete mBlinkTimer;
}

void TextCursor::move(TextPositions direction, const QString &text)
{
    switch (direction) {
        case TextPositions::Beginning:
            moveCursorAtBeginning();
            break;
        case TextPositions::End:
            moveCursorAtEnd(text);
            break;
        case TextPositions::NextWordBeginning:
            moveCursorAtNextWordBeginning(text);
            break;
        case TextPositions::Next:
            moveCursorForwardBy(text, 1);
            break;
        case TextPositions::PreviousWordBeginning:
            moveCursorAtPreviousWordBeginning(text);
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

void TextCursor::moveForwardBy(const QString &text, int moveBy)
{
	moveCursorForwardBy(text, moveBy);
	mIsVisible = true;
}

void TextCursor::start()
{
	mIsVisible = true;
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

void TextCursor::moveCursorAtBeginning()
{
    mPosition = 0;
}

void TextCursor::moveCursorAtEnd(const QString &text)
{
    mPosition = text.length();
}

void TextCursor::moveCursorAtNextWordBeginning(const QString &text)
{
    int lastSpacePos{-1};
    int pos{mPosition};

    while (pos < text.length()) {
        if (text.at(pos).isSpace()) {
            lastSpacePos = pos;
        } else {
            if (lastSpacePos >= 0) {
                break;
            }
        }
        ++ pos;
    }

    mPosition = pos;
}

void TextCursor::moveCursorForwardBy(const QString &text, int moveBy)
{
    mPosition += moveBy;
    if (mPosition > text.length()) {
        mPosition = mPosition - text.length() - 1;
    }
}

void TextCursor::moveCursorAtPreviousWordBeginning(const QString &text)
{
    int lastNonSpacePos{-1};
    int pos{mPosition-1};

    while (pos >= 0) {
        if (text.at(pos).isSpace()) {
            if (lastNonSpacePos >= 0) {
                break;
            }
        } else {
            lastNonSpacePos = pos;
        }
        -- pos;
    }

    if (lastNonSpacePos >= 0) {
        mPosition = lastNonSpacePos;
    } else {
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

void TextCursor::connectSlots()
{
	connect(mBlinkTimer, &QTimer::timeout, [this]()
	{
		mIsVisible = !mIsVisible;
		emit tick();
	});
}

} // namespace kImageAnnotator

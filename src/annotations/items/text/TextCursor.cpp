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

TextCursor::TextCursor(QTextDocument *document) :
	mInnerTextCursor(new QTextCursor(document)),
	mBlinkTimer(new QTimer(this))
{
	connectSlots();
}

TextCursor::TextCursor(const TextCursor &other) :
	mInnerTextCursor(new QTextCursor(*other.mInnerTextCursor)),
	mBlinkTimer(new QTimer(this))
{
	connectSlots();
}

TextCursor::~TextCursor()
{
	delete mInnerTextCursor;
    delete mBlinkTimer;
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
    return mInnerTextCursor->position();
}

void TextCursor::setPosition(int newPosition)
{
    mInnerTextCursor->setPosition(newPosition);
	mIsVisible = true;
}

bool TextCursor::isVisible() const
{
    return mIsVisible;
}

void TextCursor::insertText(const QString &text)
{
	mInnerTextCursor->insertText(text);
	mIsVisible = true;
}

void TextCursor::deleteChar()
{
	mInnerTextCursor->deleteChar();
	mIsVisible = true;
}

void TextCursor::deletePreviousChar()
{
	mInnerTextCursor->deletePreviousChar();
	mIsVisible = true;
}

void TextCursor::movePosition(QTextCursor::MoveOperation operation)
{
	mInnerTextCursor->movePosition(operation);
	mIsVisible = true;
}

QString TextCursor::selectedText() const
{
	return mInnerTextCursor->selectedText();
}

void TextCursor::removeSelectedText()
{
	mInnerTextCursor->removeSelectedText();
}

void TextCursor::select(QTextCursor::SelectionType selection)
{
	mInnerTextCursor->select(selection);
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

/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "AnnotationTextHandler.h"

namespace kImageAnnotator {

AnnotationTextHandler::AnnotationTextHandler() :
	mIsInEditMode(false)
{
	setupEditModeOutlinePen();
	connectSlots();
}

AnnotationTextHandler::AnnotationTextHandler(const AnnotationTextHandler &other) :
	mText(other.mText),
	mTextCursor(other.mTextCursor),
	mIsInEditMode(false)
{
	setupEditModeOutlinePen();
	connectSlots();
}

void AnnotationTextHandler::insertText(const QString &text)
{
	mText.insert(mTextCursor.position(), text);
	mTextCursor.move(TextPositions::Next, mText);
	emit changed();
}

void AnnotationTextHandler::removeText(TextPositions direction)
{
	auto currentCursorPos = mTextCursor.position();
	if (direction == TextPositions::Previous) {
		if (currentCursorPos == 0) {
			return;
		}
		mText.remove(currentCursorPos - 1, 1);
		moveCursor(TextPositions::Previous);
	} else if (direction == TextPositions::Next) {
		if (currentCursorPos >= mText.length()) {
			return;
		}
		mText.remove(currentCursorPos, 1);
	}
}

void AnnotationTextHandler::moveCursor(TextPositions direction)
{
	mTextCursor.move(direction, mText);
}

void AnnotationTextHandler::pasteText()
{
	auto clipboard = QApplication::clipboard();
	if (clipboard->text().isEmpty()) {
		return;
	}
	mText.insert(mTextCursor.position(), clipboard->text());
	mTextCursor.setPosition(mTextCursor.position() + clipboard->text().length());
}

void AnnotationTextHandler::enableEditing()
{
	mTextCursor.start();
	mIgnoreShortcutsFilter.apply();
	mIsInEditMode = true;
	emit changed();
}

void AnnotationTextHandler::disableEditing()
{
	mTextCursor.stop();
	mIgnoreShortcutsFilter.remove();
	mIsInEditMode = false;
	emit changed();
}

void AnnotationTextHandler::paintText(QPainter *painter, QRectF *rect, const QFont &font, const QColor &color, int margin, bool isShadowEnabled)
{
	auto textArea = rect->toRect();
	if (mIsInEditMode && textArea.isValid()) {
		painter->setBrush(Qt::NoBrush);
		painter->setPen(mEditModeOutlinePen);
		painter->drawRect(textArea);
	}

	// Workaround for issue #70 / #184 -> Cursor not drawn with with Qt 5.9
	// https://bugreports.qt.io/browse/QTBUG-82022
	if (mIsInEditMode && isShadowEnabled) {
		painter->setBrush(QColor(255,255,255,50));
		painter->drawRect(*rect);
	}

	// Paint text
	painter->setPen(color);

	painter->setClipRect(rect->adjusted(margin, margin, -margin, -margin));

	QFontMetrics fontMetrics(font);
	auto boxHeight = 0;

	QTextDocument document(mText);
	for (auto block = document.begin(); block != document.end(); block = block.next()) {
		auto blockPosition = block.position();
		auto blockLength = block.length();
		QTextLayout textLayout(block);
		textLayout.setCacheEnabled(true);
		textLayout.setFont(font);
		auto blockHeight = 0;
		textLayout.setCacheEnabled(true);

		textLayout.beginLayout();
		while (true) {
			auto line = textLayout.createLine();
			if (!line.isValid()) {
				break;
			}

			line.setLineWidth(textArea.width() - margin * 2);
			blockHeight += fontMetrics.leading();
			line.setPosition(textArea.adjusted(margin, margin, 0, 0).topLeft());
			blockHeight += line.height();
		}
		textLayout.endLayout();

		textLayout.draw(painter, QPoint(0, boxHeight));

		if (mTextCursor.isVisible() && isCursorInBlock(blockPosition, blockLength)) {
			textLayout.drawCursor(painter, QPointF(0, boxHeight), mTextCursor.position() - blockPosition, 1);
		}
		boxHeight += blockHeight;
	}
}

void AnnotationTextHandler::updateRect(QRectF *rect, const QFont &font, int margin) const
{
	auto newRect = getTextRect(rect, font, margin).normalized();
	auto currentRect = rect->normalized();
	if (newRect.width() > currentRect.width()) {
		currentRect.setWidth(newRect.width());
	}
	if (newRect.height() > currentRect.height()) {
		currentRect.setHeight(newRect.height());
	}
	rect->setRect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height());
}

bool AnnotationTextHandler::isCursorInBlock(int blockPosition, int blockLength) const
{
	return mTextCursor.position() >= blockPosition && mTextCursor.position() < blockPosition + blockLength;
}

void AnnotationTextHandler::setupEditModeOutlinePen()
{
	mEditModeOutlinePen.setColor(Qt::white);
	mEditModeOutlinePen.setWidthF(1);
	mEditModeOutlinePen.setStyle(Qt::DotLine);
}

QRect AnnotationTextHandler::getTextRect(QRectF *rect, const QFont& font, int margin) const
{
	QFontMetrics fontMetrics(font);
	auto newRect = fontMetrics.boundingRect(rect->toRect().normalized(), Qt::AlignLeft, mText);
	newRect.adjust(0, 2, (margin * 2) + 2, margin * 2);
	return newRect;
}

void AnnotationTextHandler::handleKeyEvent(QKeyEvent *event)
{
	mKeyInputHelper.handleKeyPress(event);
	emit changed();
}

void AnnotationTextHandler::connectSlots()
{
	connect(&mKeyInputHelper, &KeyInputHelper::move, this, &AnnotationTextHandler::moveCursor);
	connect(&mKeyInputHelper, &KeyInputHelper::insert, this, &AnnotationTextHandler::insertText);
	connect(&mKeyInputHelper, &KeyInputHelper::remove, this, &AnnotationTextHandler::removeText);
	connect(&mKeyInputHelper, &KeyInputHelper::paste, this, &AnnotationTextHandler::pasteText);
	connect(&mKeyInputHelper, &KeyInputHelper::escape, this, &AnnotationTextHandler::finished);
	connect(&mTextCursor, &TextCursor::tick, this, &AnnotationTextHandler::changed);
}

} // namespace kImageAnnotator

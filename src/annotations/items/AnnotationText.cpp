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

#include "AnnotationText.h"

namespace kImageAnnotator {

AnnotationText::AnnotationText(const QPointF &startPosition, AnnotationTextProperties *properties) : AbstractAnnotationRect(startPosition, properties)
{
	setFlag(QGraphicsItem::ItemIsFocusable, true);
	connectSlots();
	setupEditModeOutlinePen();
}

AnnotationText::AnnotationText(const AnnotationText &other) : AbstractAnnotationRect(other)
{
	mText = other.mText;

	setFlag(QGraphicsItem::ItemIsFocusable, true);
	connectSlots();
	setupEditModeOutlinePen();
}

void AnnotationText::updateShape()
{
	QPainterPath path;
	path.addRect(*mRect);
	setShape(path);
}

void AnnotationText::focusOutEvent(QFocusEvent *event)
{
	disableEditing();
	QGraphicsItem::focusOutEvent(event);
}

void AnnotationText::keyPressEvent(QKeyEvent *event)
{
	mKeyInputHelper.handleKeyPress(event);
	adjustRect();
}

void AnnotationText::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	// Paint border
	AbstractAnnotationRect::paint(painter, style, widget);

	auto textArea = mRect->normalized();
	if (mIsInEditMode) {
		setupEditModeOutlinePen();
		painter->setPen(mEditModeOutlinePen);
		painter->drawRect(textArea);
	}

	// Paint text
	painter->setPen(properties()->textColor());
	auto margine = properties()->Width();

	painter->setClipRect(boundingRect().adjusted(margine, margine, -margine, -margine));

	QFontMetrics fontMetrics(properties()->font());
	auto boxHeight = 0;

	QTextDocument document(mText);
	for (auto block = document.begin(); block != document.end(); block = block.next()) {
		auto blockPosition = block.position();
		auto blockLength = block.length();
		QTextLayout textLayout(block);
		textLayout.setFont(properties()->font());
		auto blockHeight = 0;
		textLayout.setCacheEnabled(true);

		textLayout.beginLayout();
		while (true) {
			auto line = textLayout.createLine();
			if (!line.isValid()) {
				break;
			}

			line.setLineWidth(textArea.width() - margine * 2);
			blockHeight += fontMetrics.leading();
			line.setPosition(textArea.adjusted(margine, margine, 0, 0).topLeft());
			blockHeight += line.height();
		}
		textLayout.endLayout();

		textLayout.draw(painter, QPoint(0, boxHeight));

		if (mTextCursor.isVisible() && (mTextCursor.position() >= blockPosition && mTextCursor.position() < blockPosition + blockLength)) {
			textLayout.drawCursor(painter, QPointF(0, boxHeight), mTextCursor.position() - blockPosition, 1);
		}
		boxHeight += blockHeight;
	}
}

void AnnotationText::finish()
{
	enableEditing();
}

const AnnotationTextProperties *AnnotationText::properties() const
{
	return dynamic_cast<const AnnotationTextProperties *>(AbstractAnnotationItem::properties());
}

ToolTypes AnnotationText::toolType() const
{
	return ToolTypes::Text;
}

QPainterPath AnnotationText::shape() const
{
	auto path = AbstractAnnotationItem::shape();
	path.addRect(getTextRect());
	return path;
}

void AnnotationText::setupEditModeOutlinePen()
{
	mEditModeOutlinePen.setColor(Qt::white);
	mEditModeOutlinePen.setWidthF(0.5);
	mEditModeOutlinePen.setStyle(Qt::DotLine);
}

void AnnotationText::removeText(TextPositions direction)
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

void AnnotationText::insertText(const QString &text)
{
	mText.insert(mTextCursor.position(), text);
	mTextCursor.move(TextPositions::Next, mText);
}

void AnnotationText::moveCursor(TextPositions direction)
{
	mTextCursor.move(direction, mText);
}

void AnnotationText::pasteText()
{
	auto clipboard = QApplication::clipboard();
	if (clipboard->text().isEmpty()) {
		return;
	}
	mText.insert(mTextCursor.position(), clipboard->text());
	mTextCursor.setPosition(mTextCursor.position() + clipboard->text().length());
}

void AnnotationText::escape()
{
	clearFocus();
}

void AnnotationText::adjustRect()
{
	prepareGeometryChange();
	auto newRect = getTextRect();
	if (newRect.width() > mRect->width()) {
		mRect->setWidth(newRect.width());
	}
	if (newRect.height() > mRect->height()) {
		mRect->setHeight(newRect.height());
	}
	updateShape();
}

void AnnotationText::connectSlots()
{
	connect(&mKeyInputHelper, &KeyInputHelper::move, this, &AnnotationText::moveCursor);
	connect(&mKeyInputHelper, &KeyInputHelper::insert, this, &AnnotationText::insertText);
	connect(&mKeyInputHelper, &KeyInputHelper::remove, this, &AnnotationText::removeText);
	connect(&mKeyInputHelper, &KeyInputHelper::paste, this, &AnnotationText::pasteText);
	connect(&mKeyInputHelper, &KeyInputHelper::escape, this, &AnnotationText::escape);
	connect(&mTextCursor, &TextCursor::tick, [this]()
	{
		prepareGeometryChange();
	});
}

QRect AnnotationText::getTextRect() const
{
	QFontMetrics fontMetrics(properties()->font());
	auto margin = properties()->Width();
	auto newRect = fontMetrics.boundingRect(mRect->toRect().normalized(), Qt::AlignLeft, mText);
	newRect.adjust(0, 0, margin * 2, margin * 2);
	return newRect;
}

void AnnotationText::enableEditing()
{
    adjustRect();
    setFocus();

    mTextCursor.start();
    mIgnoreShortcutsFilter.apply();
    mIsInEditMode = true;
}

void AnnotationText::disableEditing()
{
    mTextCursor.stop();
    mIgnoreShortcutsFilter.remove();
    mIsInEditMode = false;
}

} // namespace kImageAnnotator

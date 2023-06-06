/*
 * Copyright (C) 2023 Damir Porobic <damir.porobic@gmx.com>
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

#include "TextHandlerItem.h"

namespace kImageAnnotator {

TextHandlerItem::TextHandlerItem(AbstractAnnotationItem *parentItem) :
	QGraphicsTextItem(parentItem),
	mIsFixedTextRectSize(false)
{
	connectSlots();
	enableEditing();
}


TextHandlerItem::TextHandlerItem(const TextHandlerItem &other, AbstractAnnotationItem *parentItem) :
	QGraphicsTextItem(other.toPlainText(), parentItem),
	mIsFixedTextRectSize(other.mIsFixedTextRectSize)
{
	connectSlots();

	document()->setPageSize(other.document()->pageSize());

	auto currentTextCursor = textCursor();
	currentTextCursor.setPosition(other.textCursor().position());
	setTextCursor(currentTextCursor);
}

void TextHandlerItem::enableEditing()
{
	setTextInteractionFlags(Qt::TextEditorInteraction);
	setFocus();
}

void TextHandlerItem::disableEditing()
{
	clearSelection();
	setTextInteractionFlags(Qt::NoTextInteraction);
	clearFocus();
}

bool TextHandlerItem::isEditing() const
{
	return textInteractionFlags() == Qt::TextEditorInteraction;
}

QRect TextHandlerItem::textRect() const
{
	auto rect = boundingRect().toRect().normalized();
	auto position = pos().toPoint();
	return { position.x(), position.y(), rect.width(), rect.height() };
}

void TextHandlerItem::setTextRect(const QRect &rect)
{
	mIsFixedTextRectSize = true;
	document()->setPageSize(rect.size());
	setPos(rect.topLeft());
}

QRectF TextHandlerItem::boundingRect() const 
{
	if(mIsFixedTextRectSize) {
		auto position = QGraphicsTextItem::boundingRect().topLeft();
		return { position, document()->pageSize() };
	} else {
		return QGraphicsTextItem::boundingRect();
	}
}

void TextHandlerItem::setTextProperties(const TextPropertiesPtr &properties)
{
	setFont(properties->font());
	setDefaultTextColor(properties->textColor());

	emit textRectChanged();
}

QSize TextHandlerItem::minimumSize() const
{
	return ScaledSizeProvider::scaledSize(QSize(10, 30));
}

void TextHandlerItem::focusOutEvent(QFocusEvent *event)
{
	disableEditing();
	QGraphicsTextItem::focusOutEvent(event);
}

void TextHandlerItem::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape) {
		disableEditing();
	} else {
		QGraphicsTextItem::keyPressEvent(event);
	}
}

void TextHandlerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	// Workaround for issue #70 / #184 -> Cursor not drawn with Qt 5.9
	// https://bugreports.qt.io/browse/QTBUG-82022
	if (isEditing()) {
		painter->setBrush(QColor(255,255,255,50));
		painter->drawRect(boundingRect());
	}

	if (isEditing()) {
		QGraphicsTextItem::paint(painter, style, widget);
	} else {
		QStyleOptionGraphicsItem myOption(*style);
		myOption.state &= ~QStyle::State_Selected;
		QGraphicsTextItem::paint(painter, &myOption, widget);
	}

	if(isEditing() && isTextOutsideVisibleRect()) {
		auto offset = 7;
		auto size = QSizeF(14, 4);
		auto position = QPointF(boundingRect().center().x() - (size.width() / 2), boundingRect().bottom() - offset);
		auto rect = QRectF(position, size);

		QPainterPath path;
		path.moveTo(rect.left() + (rect.width() / 2), rect.bottom());
		path.lineTo(rect.topLeft());
		path.lineTo(rect.topRight());
		path.lineTo(rect.left() + (rect.width() / 2), rect.bottom());

		painter->setRenderHint(QPainter::Antialiasing, true);
		painter->fillPath(path, QBrush(QColor (Qt::red))); // Draw fill
		painter->setPen(Qt::black);
		painter->drawPath(path);   // Draw Outline
	}
}

void TextHandlerItem::clearSelection()
{
	auto currentTextCursor = textCursor();
	currentTextCursor.clearSelection();
	setTextCursor(currentTextCursor);
}

bool TextHandlerItem::isTextOutsideVisibleRect() const
{
	return document()->pageCount() > 1;
}

void TextHandlerItem::connectSlots() const
{
	connect(document(), &QTextDocument::contentsChanged, this, &TextHandlerItem::textRectChanged);
}

} // namespace kImageAnnotator
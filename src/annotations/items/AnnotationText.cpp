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

#include "AnnotationText.h"

namespace kImageAnnotator {

AnnotationText::AnnotationText(const QPointF &startPosition, const TextPropertiesPtr &properties) :
	AbstractAnnotationRect(startPosition, properties)
{
	setupFlags();
	connectSlots();
}

AnnotationText::AnnotationText(const AnnotationText &other) :
	AbstractAnnotationRect(other),
	mTextHandler(other.mTextHandler)
{
	setupFlags();
	connectSlots();
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
	QGraphicsWidget::focusOutEvent(event);
}

void AnnotationText::keyPressEvent(QKeyEvent *event)
{
	mTextHandler.handleKeyEvent(event);
}

void AnnotationText::inputMethodEvent(QInputMethodEvent *event)
{
	mTextHandler.insertText(event->commitString());
}

void AnnotationText::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	// Paint border
	AbstractAnnotationRect::paint(painter, style, widget);

	// Paint Text
	auto font = textProperties()->font();
	auto color = textProperties()->textColor();
	auto margin = textProperties()->width();
	auto isShadowEnabled = properties()->shadowEnabled();
	mTextHandler.paintText(painter, mRect, font, color, margin, isShadowEnabled);
}

void AnnotationText::finish()
{
	enableEditing();
}

Tools AnnotationText::toolType() const
{
	return Tools::Text;
}

QPainterPath AnnotationText::shape() const
{
	auto path = AbstractAnnotationItem::shape();
	auto font = textProperties()->font();
	auto margin = textProperties()->width();
	path.addRect(mTextHandler.getTextRect(mRect, font, margin));
	return path;
}

void AnnotationText::escape()
{
	clearFocus();
}

void AnnotationText::refresh()
{
	prepareGeometryChange();
	auto font = textProperties()->font();
	auto margin = textProperties()->width();
	mTextHandler.updateRect(mRect, font, margin);
	updateShape();
}

void AnnotationText::connectSlots()
{
	connect(&mTextHandler, &AnnotationTextHandler::changed, this, &AnnotationText::refresh);
	connect(&mTextHandler, &AnnotationTextHandler::finished, this, &AnnotationText::escape);
}

void AnnotationText::enableEditing()
{
    setFocus();
	mTextHandler.enableEditing();
}

void AnnotationText::disableEditing()
{
	mTextHandler.disableEditing();
}

TextPropertiesPtr AnnotationText::textProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationTextProperties>();
}

void AnnotationText::setupFlags()
{
	setFlag(ItemIsFocusable, true);
	setFlag(ItemAcceptsInputMethod, true);
}

} // namespace kImageAnnotator

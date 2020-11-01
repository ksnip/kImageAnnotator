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

#include "AnnotationTextPointer.h"

namespace kImageAnnotator {

AnnotationTextPointer::AnnotationTextPointer(const QPointF &startPosition, const TextPropertiesPtr &properties) :
	AbstractAnnotationPointerRect(startPosition, properties)
{
	setupFlags();
	connectSlots();
	mRect->setWidth(10);
	mRect->setHeight(26);
}

AnnotationTextPointer::AnnotationTextPointer(const AnnotationTextPointer &other) :
	AbstractAnnotationPointerRect(other),
	mTextHandler(other.mTextHandler)
{
	setupFlags();
	connectSlots();
}

void AnnotationTextPointer::finish()
{
	enableEditing();
}

Tools AnnotationTextPointer::toolType() const
{
	return Tools::TextPointer;
}

QPainterPath AnnotationTextPointer::shape() const
{
	auto path = AbstractAnnotationItem::shape();
	auto font = textProperties()->font();
	auto margin = textProperties()->width();
	path.addRect(mTextHandler.getTextRect(mRect, font, margin));
	return path;
}

void AnnotationTextPointer::enableEditing()
{
	setFocus();
	mTextHandler.enableEditing();
}

void AnnotationTextPointer::disableEditing()
{
	mTextHandler.disableEditing();
}

TextPropertiesPtr AnnotationTextPointer::textProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationTextProperties>();
}

void AnnotationTextPointer::updateShape()
{
	auto line = QLineF(mRect->center(), mPointer);
	auto pointerWidth = qMin(mRect->width(), mRect->height()) * 0.7;
	auto pointer = AnnotationShapeCreator::createPointer(pointerWidth, line.length());
	auto finishedPointer = AnnotationShapeCreator::translate(pointer, mPointer, -line.angle());

	QPainterPath path(mRect->center());
	path.setFillRule(Qt::WindingFill);
	path.addPolygon(finishedPointer);
	path.closeSubpath();
	path.addRect(*mRect);
	auto painterPath = path.simplified();
	setShape(painterPath);
}

void AnnotationTextPointer::focusOutEvent(QFocusEvent *event)
{
	disableEditing();
	QGraphicsWidget::focusOutEvent(event);
}

void AnnotationTextPointer::keyPressEvent(QKeyEvent *event)
{
	mTextHandler.handleKeyEvent(event);
}

void AnnotationTextPointer::inputMethodEvent(QInputMethodEvent *event)
{
	mTextHandler.insertText(event->commitString());
}

void AnnotationTextPointer::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	// Paint border
	AbstractAnnotationRect::paint(painter, style, widget);

	// Paint Text
	auto font = textProperties()->font();
	auto color = textProperties()->textColor();
	auto margin = textProperties()->width();
	mTextHandler.paintText(painter, mRect, font, color, margin);
}

void AnnotationTextPointer::connectSlots()
{
	connect(&mTextHandler, &AnnotationTextHandler::changed, this, &AnnotationTextPointer::refresh);
	connect(&mTextHandler, &AnnotationTextHandler::finished, this, &AnnotationTextPointer::escape);
}

void AnnotationTextPointer::setupFlags()
{
	setFlag(ItemIsFocusable, true);
	setFlag(ItemAcceptsInputMethod, true);
}

void AnnotationTextPointer::escape()
{
	clearFocus();
}

void AnnotationTextPointer::refresh()
{
	prepareGeometryChange();
	auto font = textProperties()->font();
	auto margin = textProperties()->width();
	mTextHandler.updateRect(mRect, font, margin);
	updateShape();
}

} // namespace kImageAnnotator
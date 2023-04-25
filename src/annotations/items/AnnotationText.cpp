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
	AbstractAnnotationRect(startPosition, properties),
	mTextHandlerItem(new TextHandlerItem(this))
{
	connectSlots();

	mTextHandlerItem->setPos(startPosition);
	setMinimumSize(mTextHandlerItem->minimumSize());

	updateProperties();
	refresh();
}

AnnotationText::AnnotationText(const AnnotationText &other) :
	AbstractAnnotationRect(other),
	mTextHandlerItem(new TextHandlerItem(*other.mTextHandlerItem))
{
	connectSlots();
	setMinimumSize(mTextHandlerItem->minimumSize());
	refresh();
}

AnnotationText::~AnnotationText()
{
	delete mTextHandlerItem;
}

void AnnotationText::updateShape()
{
	QPainterPath path;
	path.addRect(*mRect);
	setShape(path);
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
	auto itemShape = AbstractAnnotationRect::shape();
	itemShape.addRect(mTextHandlerItem->textRect());
	return itemShape;
}

void AnnotationText::refresh()
{
	prepareGeometryChange();
	*mRect = RectSizeHelper::setSizeButKeepDirection(*mRect, mTextHandlerItem->boundingRect().size());
	updateShape();
}

void AnnotationText::connectSlots()
{
	connect(mTextHandlerItem, &TextHandlerItem::textRectChanged, this, &AnnotationText::refresh);
	connect(this, &AnnotationText::propertiesChanged, this, &AnnotationText::updateProperties);
}

void AnnotationText::enableEditing()
{
	mTextHandlerItem->enableEditing();
}

void AnnotationText::disableEditing()
{
	mTextHandlerItem->disableEditing();
}

TextPropertiesPtr AnnotationText::textProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationTextProperties>();
}

void AnnotationText::setPosition(const QPointF &newPosition)
{
	AbstractAnnotationRect::setPosition(newPosition);
	mTextHandlerItem->setPos(newPosition);
}

void AnnotationText::addPoint(const QPointF &position, bool modified)
{
	AbstractAnnotationRect::addPoint(position, modified);
	mTextHandlerItem->setTextRect(boundingRect().toRect());
}

void AnnotationText::setPointAt(const QPointF &point, int index, bool keepAspectRatio)
{
	AbstractAnnotationRect::setPointAt(point, index, keepAspectRatio);
	mTextHandlerItem->setTextRect(boundingRect().toRect());
}

void AnnotationText::updateProperties()
{
	mTextHandlerItem->setTextProperties(textProperties());
}

} // namespace kImageAnnotator

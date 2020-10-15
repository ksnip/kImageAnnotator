/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationNumberPointer.h"

namespace kImageAnnotator {

AnnotationNumberPointer::AnnotationNumberPointer(const QPointF &startPosition, const TextPropertiesPtr &properties) :
	AbstractAnnotationLine(startPosition, properties),
	mRect(new QRectF)
{
	mLine->setP2(startPosition);
	mRect->moveCenter(startPosition);
}

AnnotationNumberPointer::AnnotationNumberPointer(const AnnotationNumberPointer &other) :
	AbstractAnnotationLine(other),
	BaseAnnotationNumber(other),
	mRect(new QRectF)
{
	mRect = new QRectF();
	updateShape();
}

AnnotationNumberPointer::~AnnotationNumberPointer()
{
	delete mRect;
}

Tools AnnotationNumberPointer::toolType() const
{
	return Tools::NumberPointer;
}

QPainterPath AnnotationNumberPointer::shape() const
{
	auto path = AbstractAnnotationLine::shape();
	path.addRect(*mRect);
	return path;
}

TextPropertiesPtr AnnotationNumberPointer::textProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationTextProperties>();
}

void AnnotationNumberPointer::finish()
{
	auto rectWidth = mRect->width();
	if(mLine->length() <= rectWidth / 2) {
		auto offset = rectWidth * 0.8;
		mLine->setP2(mLine->p1() + QPointF(offset, -offset));
		updateRect();
	}
	AbstractAnnotationItem::finish();
}

void AnnotationNumberPointer::updateShape()
{
	mRect->moveCenter(mLine->p1());
	BaseAnnotationNumber::updateRect(mRect, textProperties()->font());

	auto pointer = AnnotationShapeCreator::createPointer(mRect->width() * 0.7, mLine->length());
	auto finishedPointer = AnnotationShapeCreator::translate(pointer, mLine->p2(), -mLine->angle());

	QPainterPath path(mLine->p1());
	path.setFillRule(Qt::WindingFill);
	path.addPolygon(finishedPointer);
	path.closeSubpath();
	path.addEllipse(*mRect);
	auto painterPath = path.simplified();
	setShape(painterPath);
}

void AnnotationNumberPointer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	AbstractAnnotationLine::paint(painter, option, widget);

	painter->setFont(textProperties()->font());
	painter->setPen(properties()->textColor());
	painter->drawText(*mRect, Qt::AlignCenter, numberString());
}

void AnnotationNumberPointer::updateProperties(const PropertiesPtr &properties)
{
	AbstractAnnotationItem::updateProperties(properties);
	updateRect();
}

void AnnotationNumberPointer::updateRect()
{
	prepareGeometryChange();
	updateShape();
}

} // namespace kImageAnnotator

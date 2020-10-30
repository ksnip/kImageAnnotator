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
	AbstractAnnotationPointerRect(startPosition, properties)
{
}

AnnotationNumberPointer::AnnotationNumberPointer(const AnnotationNumberPointer &other) :
	AbstractAnnotationPointerRect(other),
	BaseAnnotationNumber(other)
{
	BaseAnnotationNumber::updateRect(mRect, textProperties()->font());

	updateShape();
}

Tools AnnotationNumberPointer::toolType() const
{
	return Tools::NumberPointer;
}

TextPropertiesPtr AnnotationNumberPointer::textProperties() const
{
	return AbstractAnnotationItem::properties().staticCast<AnnotationTextProperties>();
}

void AnnotationNumberPointer::updateShape()
{
	auto line = QLineF(mRect->center(), mPointer);
	auto pointerWidth = qMin(mRect->width(), mRect->height()) * 0.7;
	auto pointer = AnnotationShapeCreator::createPointer(pointerWidth, line.length());
	auto finishedPointer = AnnotationShapeCreator::translate(pointer, mPointer, -line.angle());

	QPainterPath path(mRect->center());
	path.setFillRule(Qt::WindingFill);
	path.addPolygon(finishedPointer);
	path.closeSubpath();
	path.addEllipse(*mRect);
	auto painterPath = path.simplified();
	setShape(painterPath);
}

void AnnotationNumberPointer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	AbstractAnnotationPointerRect::paint(painter, option, widget);

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
	BaseAnnotationNumber::updateRect(mRect, textProperties()->font());
	updateShape();
}

} // namespace kImageAnnotator

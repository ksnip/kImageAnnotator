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

#include "AnnotationNumberArrow.h"

namespace kImageAnnotator {

AnnotationNumberArrow::AnnotationNumberArrow(const QPointF &startPosition, const kImageAnnotator::TextPropertiesPtr &properties) :
	AnnotationNumberPointer(startPosition, properties)
{
}

AnnotationNumberArrow::AnnotationNumberArrow(const kImageAnnotator::AnnotationNumberArrow &other) :
	AnnotationNumberPointer(other)
{
}

Tools AnnotationNumberArrow::toolType() const
{
	return Tools::NumberArrow;
}

void AnnotationNumberArrow::updateShape()
{
	QLineF tmpLine(mPointer, mRect->center());
	tmpLine.setLength(tmpLine.length() - mRect->width() / 2);
	QLineF shaft(tmpLine.p2(), tmpLine.p1());
	shaft.setLength(tmpLine.length() - 5);

	auto arrow = AnnotationShapeCreator::createArrowHead(properties()->width() / 2);
	arrow = AnnotationShapeCreator::translate(arrow, mPointer, -shaft.angle());

	mRect->moveCenter(mRect->center());

	mArrowShape = QPainterPath(shaft.p1());
	mArrowShape.setFillRule(Qt::WindingFill);
	mArrowShape.lineTo(shaft.p2());
	mArrowShape.addPolygon(arrow);

	QPainterPath path(mArrowShape);
	path.addEllipse(*mRect);
	path.closeSubpath();
	setShape(path);
}

void AnnotationNumberArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	adjustPainter(painter);

	painter->setPen(painterPen());
	painter->setBrush(properties()->color());

	// Draw Arrow
	painter->drawPath(mArrowShape);

	// Draw Ellipse
	if(!hasFill()) {
		painter->setBrush(Qt::NoBrush);
	}
	if(!hasBorder()) {
		painter->setPen(Qt::NoPen);
	}
	painter->drawEllipse(*mRect);

	// Draw Number
	painter->setFont(textProperties()->font());
	painter->setPen(properties()->textColor());
	painter->drawText(*mRect, Qt::AlignCenter, numberString());
}

} // namespace kImageAnnotator
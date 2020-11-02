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

#include "AnnotationTextArrow.h"

namespace kImageAnnotator {

AnnotationTextArrow::AnnotationTextArrow(const QPointF &startPosition, const TextPropertiesPtr &properties) :
	AnnotationTextPointer(startPosition, properties)
{

}

AnnotationTextArrow::AnnotationTextArrow(const AnnotationTextArrow &other) :
	AnnotationTextPointer(other)
{

}

Tools AnnotationTextArrow::toolType() const
{
	return Tools::TextArrow;
}

void AnnotationTextArrow::updateShape()
{
	QLineF tmpLine(mPointer, mRect->center());
	QPointF intersectionPoint = ShapeHelper::intersectionBetweenRectAndLineFromCenter(tmpLine, *mRect);

	QLineF shaft(intersectionPoint, mPointer);
	shaft.setLength(shaft.length() - 5);

	auto arrow = AnnotationShapeCreator::createArrowHead(properties()->width() / 2);
	arrow = AnnotationShapeCreator::translate(arrow, mPointer, -shaft.angle());

	mRect->moveCenter(mRect->center());

	mArrowShape = QPainterPath(shaft.p1());
	mArrowShape.setFillRule(Qt::WindingFill);
	mArrowShape.lineTo(shaft.p2());
	mArrowShape.addPolygon(arrow);

	QPainterPath path(mArrowShape);
	path.addRect(*mRect);
	path.closeSubpath();
	setShape(path);
}

void AnnotationTextArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *style, QWidget *widget)
{
	adjustPainter(painter);

	painter->setPen(painterPen());
	painter->setBrush(properties()->color());

	// Draw Arrow
	painter->drawPath(mArrowShape);

	// Border and fill
	if(!hasFill()) {
		painter->setBrush(Qt::NoBrush);
	}
	if(!hasBorder()) {
		painter->setPen(Qt::NoPen);
	}
	painter->drawRect(*mRect);

	// Paint Text
	auto font = textProperties()->font();
	auto color = textProperties()->textColor();
	auto margin = textProperties()->width();
	mTextHandler.paintText(painter, mRect, font, color, margin);
}

} // namespace kImageAnnotator
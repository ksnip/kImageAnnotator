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

#include "AnnotationArrow.h"

namespace kImageAnnotator {

AnnotationArrow::AnnotationArrow(const QPointF &startPosition, const PropertiesPtr &properties) : AbstractAnnotationLine(startPosition, properties)
{
}

AnnotationArrow::AnnotationArrow(const AnnotationArrow &other) : AbstractAnnotationLine(other)
{

}

ToolTypes AnnotationArrow::toolType() const
{
	return ToolTypes::Arrow;
}

void AnnotationArrow::updateShape()
{
	QPainterPath path(mLine->p1());
	path.lineTo(mLine->p2());

	auto arrow = createArrow();
	auto finishedArrow = positionArrowHeadAtEnd(arrow);

	path.addPolygon(finishedArrow);
	path.closeSubpath();
	setShape(path);
}

QPolygonF AnnotationArrow::createArrow() const
{
	int mArrowHeadLength = 20;
	int mArrowHeadWidth = 10;
	int mArrowHeadMid = 17;

	QPointF p0(0, 0);
	QPointF p1(-mArrowHeadLength, mArrowHeadWidth);
	QPointF p2(-mArrowHeadMid, 0);
	QPointF p3(-mArrowHeadLength, -mArrowHeadWidth);

	QPolygonF arrow;
	arrow << p0 << p1 << p2 << p3 << p0;

	return arrow;
}

QPolygonF AnnotationArrow::positionArrowHeadAtEnd(const QPolygonF &arrow) const
{
	auto endX = mLine->p2().x();
	auto endY = mLine->p2().y();
	auto angle = -mLine->angle();

	return QTransform().translate(endX, endY).rotate(angle).map(arrow);
}

} // namespace kImageAnnotator

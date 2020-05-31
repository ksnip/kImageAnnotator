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
	QLineF shaft(*mLine);
	shaft.setLength(shaft.length() - 5);

	auto arrow = AnnotationShapeCreator::createArrowHead(properties()->width() / 2);
	arrow = AnnotationShapeCreator::translate(arrow, mLine->p2(), -mLine->angle());

	QPainterPath path(shaft.p1());
	path.lineTo(shaft.p2());
	path.addPolygon(arrow);
	path.closeSubpath();
	setShape(path);
}

} // namespace kImageAnnotator

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

#include "AnnotationShapeCreator.h"

namespace kImageAnnotator {

QPolygonF AnnotationShapeCreator::createPointer(qreal width, qreal length)
{
	QPointF p0(0, 0);
	QPointF p1(-length, width / 2);
	QPointF p2(-length, -width / 2);

	QPolygonF pointer;
	return pointer << p0 << p1 << p2 << p0;
}

QPolygonF AnnotationShapeCreator::createArrowHead(int scaleFactor)
{
	auto arrowHeadLength = 15 + scaleFactor;
	auto arrowHeadWidth = 5 + scaleFactor;
	auto arrowHeadMid = 13 + scaleFactor;

	QPointF p0(0, 0);
	QPointF p1(-arrowHeadLength, arrowHeadWidth);
	QPointF p2(-arrowHeadMid, 0);
	QPointF p3(-arrowHeadLength, -arrowHeadWidth);

	QPolygonF arrow;
	return arrow << p0 << p1 << p2 << p3 << p0;
}

QPolygonF AnnotationShapeCreator::translate(const QPolygonF &shape, const QPointF &pos, qreal angle)
{
	return QTransform().translate(pos.x(), pos.y()).rotate(angle).map(shape);
}

} // namespace kImageAnnotator
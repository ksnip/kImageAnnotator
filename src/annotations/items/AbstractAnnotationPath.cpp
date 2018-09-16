/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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


#include "AbstractAnnotationPath.h"

namespace kImageAnnotator {

AbstractAnnotationPath::AbstractAnnotationPath(const QPointF &startPosition, AnnotationPathProperties *properties) : AbstractAnnotationItem(properties)
{
	mPath = new QPainterPath();
	mPath->moveTo(startPosition);
	mPath->lineTo(startPosition + QPointF(1, 1));
}

AbstractAnnotationPath::~AbstractAnnotationPath()
{
	delete mPath;
}

void AbstractAnnotationPath::addPoint(const QPointF &position, bool modified)
{
	Q_UNUSED(modified)

	prepareGeometryChange();
	mPath->lineTo(position);
	updateShape();
}

void AbstractAnnotationPath::setPosition(const QPointF &newPosition)
{
	prepareGeometryChange();
	mPath->translate(newPosition - position());
	updateShape();
}

void AbstractAnnotationPath::setPointAt(const QPointF &point, int handleIndex)
{
	auto oppositeIndex = (handleIndex + 4) % 8;
	auto currentPos = ShapeHelper::rectPointAtIndex(boundingRect(), oppositeIndex);
	auto rect = ShapeHelper::setRectPointAtIndex(boundingRect(), handleIndex, point);
	if (rect.width() >= AnnotationConstants::MinResizeRectSize && rect.height() >= AnnotationConstants::MinResizeRectSize) {
		prepareGeometryChange();
		scalePath(rect);
		mPath->translate(currentPos - ShapeHelper::rectPointAtIndex(boundingRect(), oppositeIndex));
		updateShape();
	}
}

QPointF AbstractAnnotationPath::pointAt(int index) const
{
	return ShapeHelper::rectPointAtIndex(mPath->boundingRect(), index);
}

void AbstractAnnotationPath::finish()
{
	if (properties()->smoothPathEnabled()) {
		prepareGeometryChange();
		auto smoothPath = ShapeHelper::smoothOut(*mPath, properties()->smoothFactor());
		mPath->swap(smoothPath);
		updateShape();
	}
}

void AbstractAnnotationPath::scalePath(const QRectF &rect)
{
	QTransform transform;
	transform.scale(rect.width() / boundingRect().width(), rect.height() / boundingRect().height());
	auto sPath = transform.map(*mPath);
	mPath->swap(sPath);
	updateShape();
}

const AnnotationPathProperties *AbstractAnnotationPath::properties() const
{
	return dynamic_cast<const AnnotationPathProperties *>(AbstractAnnotationItem::properties());
}

} // namespace kImageAnnotator

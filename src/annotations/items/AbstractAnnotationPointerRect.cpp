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

#include "AbstractAnnotationPointerRect.h"

namespace kImageAnnotator {

AbstractAnnotationPointerRect::AbstractAnnotationPointerRect(const QPointF &startPosition, const kImageAnnotator::PropertiesPtr &properties) : 
	AbstractAnnotationRect(startPosition, properties),
	mPointerIndex(8),
	mPointer(startPosition)
{
}

AbstractAnnotationPointerRect::AbstractAnnotationPointerRect(const AbstractAnnotationPointerRect &other) :
	AbstractAnnotationRect(other),
	mPointer(QPointF(other.mPointer)),
	mPointerIndex(8)
{
}

void AbstractAnnotationPointerRect::addPoint(const QPointF &position, bool modified)
{
	prepareGeometryChange();
	mPointer = position;
	updateShape();
}

void AbstractAnnotationPointerRect::setPosition(const QPointF &newPosition)
{
	auto offset = AbstractAnnotationRect::position() - newPosition;
	mPointer -= offset;
	AbstractAnnotationRect::setPosition(newPosition);
}

void AbstractAnnotationPointerRect::setPointAt(const QPointF &point, int index, bool keepAspectRatio)
{
	Q_UNUSED(keepAspectRatio);
	if(isPointer(index)){
		mPointer = point;
		prepareGeometryChange();
		updateShape();
	} else {
		AbstractAnnotationRect::setPointAt(point, index, false);
	}
}

QPointF AbstractAnnotationPointerRect::pointAt(int index) const
{
	return isPointer(index) ? mPointer : AbstractAnnotationRect::pointAt(index);
}

void AbstractAnnotationPointerRect::finish()
{
	auto rectWidth = mRect->width();
	if(mRect->contains(mPointer)) {
		auto offset = rectWidth * 0.8;
		mPointer += QPointF(offset, -offset);
		prepareGeometryChange();
		updateShape();
	}
	AbstractAnnotationItem::finish();
}

bool AbstractAnnotationPointerRect::isPointer(int index) const
{
	return index == mPointerIndex;
}

} // namespace kImageAnnotator


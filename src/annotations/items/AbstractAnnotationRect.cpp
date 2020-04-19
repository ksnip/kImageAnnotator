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

#include "AbstractAnnotationRect.h"

namespace kImageAnnotator {

AbstractAnnotationRect::AbstractAnnotationRect(const QPointF &startPosition, const PropertiesPtr &properties) : AbstractAnnotationItem(properties)
{
	mRect = new QRectF();
	mRect->setTopLeft(startPosition);
	mRect->setBottomRight(startPosition);
}

AbstractAnnotationRect::AbstractAnnotationRect(const AbstractAnnotationRect &other) : AbstractAnnotationItem(other)
{
	mRect = new QRectF(*other.mRect);
}

AbstractAnnotationRect::~AbstractAnnotationRect()
{
	delete mRect;
}

void AbstractAnnotationRect::addPoint(const QPointF &position, bool modified)
{
	prepareGeometryChange();
	mRect->setBottomRight(position);
	makeSymmetric(modified);
	updateShape();
}

void AbstractAnnotationRect::setPosition(const QPointF &newPosition)
{
	prepareGeometryChange();
	mRect->translate(newPosition - position());
	updateShape();
}

QRectF AbstractAnnotationRect::rect() const
{
	return *mRect;
}

void AbstractAnnotationRect::setPointAt(const QPointF &point, int index)
{
	prepareGeometryChange();
	auto newRect = ShapeHelper::setRectPointAtIndex(*mRect, index, point);
	mRect->setRect(newRect.x(), newRect.y(), newRect.width(), newRect.height());
	updateShape();
}

QPointF AbstractAnnotationRect::pointAt(int index) const
{
	return ShapeHelper::rectPointAtIndex(*mRect, index);
}

void AbstractAnnotationRect::scale(qreal sx, qreal sy)
{
	prepareGeometryChange();
	QTransform transform;
	transform.scale(sx, sy);
	auto scaledRect = transform.mapRect(*mRect);
	mRect->setRect(scaledRect.x(), scaledRect.y(), scaledRect.width(), scaledRect.height());
	updateShape();
}

void AbstractAnnotationRect::makeSymmetric(bool enabled)
{
	if (enabled) {
		mRect->setHeight(MathHelper::smallerValue(mRect->height(), mRect->width()));
		mRect->setWidth(MathHelper::smallerValue(mRect->width(), mRect->height()));
	}
}

} // namespace kImageAnnotator

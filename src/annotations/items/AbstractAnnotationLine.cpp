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

#include "AbstractAnnotationLine.h"

namespace kImageAnnotator {

AbstractAnnotationLine::AbstractAnnotationLine(const QPointF &startPosition, const PropertiesPtr &properties) : AbstractAnnotationItem(properties)
{
	mLine = new QLineF();
	mLine->setP1(startPosition);
}

AbstractAnnotationLine::AbstractAnnotationLine(const AbstractAnnotationLine &other) : AbstractAnnotationItem(other)
{
	mLine = new QLineF(*other.mLine);
}

AbstractAnnotationLine::~AbstractAnnotationLine()
{
	delete mLine;
}

void AbstractAnnotationLine::addPoint(const QPointF &position, bool modified)
{
	prepareGeometryChange();
	mLine->setP2(position);
	snapToAngle(modified);
	updateShape();
}

void AbstractAnnotationLine::setPosition(const QPointF &newPosition)
{
	prepareGeometryChange();
	mLine->translate(newPosition - position());
	updateShape();
}

QLineF AbstractAnnotationLine::line() const
{
	return *mLine;
}

void AbstractAnnotationLine::setPointAt(const QPointF &point, int index)
{
	prepareGeometryChange();

	if (index <= 0) {
		mLine->setP1(point);
	} else {
		mLine->setP2(point);
	}

	updateShape();
}

QPointF AbstractAnnotationLine::pointAt(int index) const
{
	if (index <= 0) {
		return mLine->p1();
	} else {
		return mLine->p2();
	}
}

void AbstractAnnotationLine::scale(qreal sx, qreal sy)
{
	prepareGeometryChange();
	QTransform transform;
	transform.scale(sx, sy);
	auto scaledLine = transform.map(*mLine);
	mLine->setP1(scaledLine.p1());
	mLine->setP2(scaledLine.p2());
	updateShape();
}

void AbstractAnnotationLine::snapToAngle(bool enabled)
{
	if (enabled) {
		auto newAngle = MathHelper::roundAngleTo(mLine->angle(), 45);
		mLine->setAngle(newAngle);
	}
}

} // namespace kImageAnnotator

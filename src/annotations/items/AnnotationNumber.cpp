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

#include "AnnotationNumber.h"

namespace kImageAnnotator {

AnnotationNumber::AnnotationNumber(const QPointF &centerPosition, AnnotationTextProperties *properties)
	: AbstractAnnotationRect(centerPosition, properties)
{
	mRect->moveCenter(centerPosition);
}

AnnotationNumber::AnnotationNumber(const AnnotationNumber &other) : AbstractAnnotationRect(other)
{
	updateShape();
}

void AnnotationNumber::addPoint(const QPointF &position, bool modified)
{
	Q_UNUSED(position);
	Q_UNUSED(modified);

	// Nothing to do here
}

const AnnotationTextProperties *AnnotationNumber::properties() const
{
	return dynamic_cast<const AnnotationTextProperties *>(AbstractAnnotationItem::properties());
}

ToolTypes AnnotationNumber::toolType() const
{
	return ToolTypes::Number;
}

void AnnotationNumber::setNumber(int number)
{
	mNumberString = QString::number(number);
	updateRect();
}

int AnnotationNumber::number() const
{
	return mNumberString.toInt();
}

void AnnotationNumber::updateRect()
{
	prepareGeometryChange();
	auto center = mRect->center();
	auto size = getTextRectSize();
	mRect->setSize(size);
	mRect->moveCenter(center);
	updateShape();
}

void AnnotationNumber::updateShape()
{
	QPainterPath path;
	path.addEllipse(*mRect);
	setShape(path);
}

void AnnotationNumber::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	AbstractAnnotationRect::paint(painter, option, widget);

	painter->setFont(properties()->font());
	painter->setPen(properties()->textColor());
	painter->drawText(boundingRect(), Qt::AlignCenter, mNumberString);
}

QSizeF AnnotationNumber::getTextRectSize() const
{
	QFontMetricsF metrics(properties()->font());
	auto boundingRect = metrics.boundingRect(mNumberString).adjusted(-5, -5, 5, 5);
	auto largestSite = boundingRect.width() > boundingRect.height() ? boundingRect.width() : boundingRect.height();
	return { largestSite, largestSite };
}

} // namespace kImageAnnotator

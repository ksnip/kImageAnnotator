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

#include "AbstractAnnotationItem.h"

namespace kImageAnnotator {

AbstractAnnotationItem::AbstractAnnotationItem(AnnotationProperties *properties) : mShadowEffect(nullptr)
{
	Q_ASSERT(properties != nullptr);

	mProperties = properties;
	mShape = new QPainterPath();

	mPainterPen.setColor(mProperties->color());
	mPainterPen.setWidth(mProperties->Width());
	mPainterPen.setCapStyle(Qt::RoundCap);
	mPainterPen.setJoinStyle(Qt::RoundJoin);

	mStroker = new QPainterPathStroker(mPainterPen);

	if (mProperties->shadowEnabled()) {
		mShadowEffect = new ShadowEffect();
		setGraphicsEffect(mShadowEffect);
	}
}

AbstractAnnotationItem::AbstractAnnotationItem(const AbstractAnnotationItem &other)
{
	mProperties = new AnnotationProperties(*other.mProperties);
	mShape = new QPainterPath(*other.mShape);
	mPainterPen = other.mPainterPen;
	mStroker = new QPainterPathStroker(mPainterPen);
	mShadowEffect = other.mShadowEffect != nullptr ? new ShadowEffect() : nullptr;
}

AbstractAnnotationItem::~AbstractAnnotationItem()
{
	delete mProperties;
	delete mShape;
	delete mStroker;
}

QRectF AbstractAnnotationItem::boundingRect() const
{
	auto width = 0;
	if (!mShape->isEmpty()) {
		width = mProperties->Width() / 2;
	}
	return mShape->boundingRect().adjusted(-width, -width, width, width);
}

QPainterPath AbstractAnnotationItem::shape() const
{
	auto path = mStroker->createStroke(*mShape);
	if (hasFill()) {
		path.addPath(*mShape);
	}
	return path;
}

bool AbstractAnnotationItem::intersects(const QRectF &rect) const
{
	return shape().intersects(rect);
}

void AbstractAnnotationItem::setShape(QPainterPath &newShape)
{
	mShape->swap(newShape);
}

QPointF AbstractAnnotationItem::position()
{
	return boundingRect().topLeft();
}

const AnnotationProperties *AbstractAnnotationItem::properties() const
{
	return mProperties;
}

void AbstractAnnotationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	shiftPainterForAllOddShapeWidth(painter);

	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(mPainterPen);
	if (hasFill()) {
		painter->setBrush(mProperties->color());
	}
	painter->drawPath(*mShape);
}

void AbstractAnnotationItem::shiftPainterForAllOddShapeWidth(QPainter *painter) const
{
	if (mPainterPen.width() % 2 != 0) {
		painter->translate(0.5, 0.5);
	}
}

bool AbstractAnnotationItem::hasFill() const
{
	return mProperties->fillType() == FillTypes::Fill;
}

void AbstractAnnotationItem::finish()
{
	// By default, does nothing
}

} // namespace kImageAnnotator

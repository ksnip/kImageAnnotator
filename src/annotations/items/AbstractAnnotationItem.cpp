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

#include "AbstractAnnotationItem.h"

namespace kImageAnnotator {

AbstractAnnotationItem::AbstractAnnotationItem(const PropertiesPtr &properties)
{
	Q_ASSERT(properties != nullptr);

	updateProperties(properties);
	mPainterPen.setCapStyle(Qt::RoundCap);
	mPainterPen.setJoinStyle(Qt::RoundJoin);

	mShape = new QPainterPath();
	mStroker = new QPainterPathStroker(mPainterPen);

	updateShadow();
}

AbstractAnnotationItem::AbstractAnnotationItem(const AbstractAnnotationItem &other)
{
	mProperties = other.mProperties->clone();
	mShape = new QPainterPath(*other.mShape);
	mPainterPen = other.mPainterPen;
	mStroker = new QPainterPathStroker(mPainterPen);
	setZValue(other.zValue());
	setCursor(other.cursor());
	setOpacity(other.opacity());

	updateShadow();
}

AbstractAnnotationItem::~AbstractAnnotationItem()
{
	delete mShape;
	delete mStroker;
}

QRectF AbstractAnnotationItem::boundingRect() const
{
	auto width = 0;
	if (mShape->elementCount() > 0) {
		width = mProperties->width() * 0.5;
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

PropertiesPtr AbstractAnnotationItem::properties() const
{
	return mProperties;
}

void AbstractAnnotationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (mShape->elementCount() == 0) {
		return;
	}

	adjustPainter(painter);

	if (mShape->elementCount() == 1 && hasBorder()) {
		drawPoint(painter);
	}
	else {
		drawPath(painter);
	}
}

void AbstractAnnotationItem::adjustPainter(QPainter *painter) const
{
	painter->setCompositionMode(compositionMode());
	painter->setRenderHint(QPainter::Antialiasing, true);
	shiftPainterForAllOddShapeWidth(painter);
}

QPen AbstractAnnotationItem::painterPen() const
{
	return mPainterPen;
}

QPainter::CompositionMode AbstractAnnotationItem::compositionMode() const
{
	return QPainter::CompositionMode_Source;
}

void AbstractAnnotationItem::drawPoint(QPainter *painter) const
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mPainterPen.color());
	const auto element = mShape->elementAt(0);
	const auto width = mPainterPen.widthF();
	const auto x = element.x - 0.5 * width;
	const auto y = element.y - 0.5 * width;
	if (mPainterPen.capStyle() == Qt::RoundCap) {
		painter->drawEllipse(x, y, width, width);
	} else {
		painter->drawRect(x, y, width, width);
	}
}

void AbstractAnnotationItem::drawPath(QPainter *painter) const
{
	if (hasBorder()) {
		painter->setPen(mPainterPen);
	} else {
		painter->setPen(Qt::NoPen);
	}

	if (hasFill()) {
		painter->setBrush(mProperties->color());
	}
	painter->drawPath(*mShape);
}

void AbstractAnnotationItem::updateProperties(const PropertiesPtr &properties)
{
	mProperties = properties;
	mPainterPen.setColor(mProperties->color());
	mPainterPen.setWidth(mProperties->width());

	setOpacity(properties->opacity());

	updateShadow();
}

void AbstractAnnotationItem::shiftPainterForAllOddShapeWidth(QPainter *painter) const
{
	if (mPainterPen.width() % 2 != 0) {
		painter->translate(0.5, 0.5);
	}
}

bool AbstractAnnotationItem::hasFill() const
{
	auto fillType = mProperties->fillType();
	return fillType == FillModes::BorderAndFill || fillType == FillModes::NoBorderAndFill;
}

bool AbstractAnnotationItem::hasBorder() const
{
	auto fillType = mProperties->fillType();
	return fillType == FillModes::BorderAndFill || fillType == FillModes::BorderAndNoFill;
}

void AbstractAnnotationItem::finish()
{
	// By default, does nothing
}

bool AbstractAnnotationItem::requiresSelectionAfterCreation() const
{
	return false;
}

void AbstractAnnotationItem::setProperties(const PropertiesPtr &properties)
{
	Q_ASSERT(properties != nullptr);

	prepareGeometryChange();
	updateProperties(properties);
}

void AbstractAnnotationItem::updateShadow()
{
	if (mProperties->shadowEnabled()) {
		if(graphicsEffect() == nullptr) {
			setGraphicsEffect(new ShadowEffect());
		}
	} else {
		setGraphicsEffect(nullptr);
	}
}

} // namespace kImageAnnotator

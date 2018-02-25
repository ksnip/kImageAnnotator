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

AbstractAnnotationItem::AbstractAnnotationItem(const AnnotationItemProperties& properties)
{
    mProperties = new AnnotationItemProperties(properties);
    mShape = new QPainterPath();
}

AbstractAnnotationItem::~AbstractAnnotationItem()
{
    delete mProperties;
    delete mShape;
}

QRectF AbstractAnnotationItem::boundingRect() const
{
    return mShape->boundingRect();
}

QPainterPath AbstractAnnotationItem::shape() const
{
    return *mShape;
}

bool AbstractAnnotationItem::intersects(const QRectF& rect) const
{
    return mShape->intersects(rect);
}

void AbstractAnnotationItem::setShape(QPainterPath& newShape)
{
    mShape->swap(newShape);
}

QPointF AbstractAnnotationItem::position()
{
    return boundingRect().topLeft();
}

AnnotationItemProperties AbstractAnnotationItem::properties() const
{
    return *mProperties;
}

void AbstractAnnotationItem::setProperties(const AnnotationItemProperties& properties)
{
    *mProperties = properties;
}

void AbstractAnnotationItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPen pen;
    pen.setColor(mProperties->borderColor());
    pen.setWidth(mProperties->size());
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(mProperties->fillColor());
    painter->drawPath(*mShape);
}

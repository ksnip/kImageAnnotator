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

#include "AbstractAnnotationRect.h"

AbstractAnnotationRect::AbstractAnnotationRect(const QPointF& startPosisition, const AnnotationProperties& properties) :
    AbstractAnnotationItem(properties)
{
    mRect = new QRectF();
    mRect->setTopLeft(startPosisition);
}

AbstractAnnotationRect::~AbstractAnnotationRect()
{
    delete mRect;
}

void AbstractAnnotationRect::addPoint(const QPointF& position)
{
    prepareGeometryChange();
    mRect->setBottomRight(position);
    updateShape();
}

void AbstractAnnotationRect::setPosition(const QPointF& newPosition)
{
    prepareGeometryChange();
    mRect->translate(newPosition - position());
    updateShape();
}

QRectF AbstractAnnotationRect::rect() const
{
    return *mRect;
}

void AbstractAnnotationRect::setRect(const QRectF& rect)
{
    prepareGeometryChange();
    mRect->setRect(rect.x(), rect.y(), rect.width(), rect.height());
    updateShape();
}

void AbstractAnnotationRect::setPointAt(const QPointF& point, int index)
{
    prepareGeometryChange();

    if(index <= 0) {
        mRect->setTopLeft(point);
    } else if (index == 1){
        mRect->setTop(point.y());
    } else if (index == 2){
        mRect->setTopRight(point);
    } else if (index == 3){
        mRect->setRight(point.x());
    } else if (index == 4){
        mRect->setBottomRight(point);
    } else if (index == 5){
        mRect->setBottom(point.y());
    } else if (index == 6){
        mRect->setBottomLeft(point);
    } else {
        mRect->setLeft(point.x());
    }

    updateShape();
}

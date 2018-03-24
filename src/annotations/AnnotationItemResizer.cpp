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

#include "AnnotationItemResizer.h"

AnnotationItemResizer::AnnotationItemResizer()
{
    mControlPointSize = 10;
    mControlPoints = new ControlPoints(mControlPointSize);
    mAnnotationItem = nullptr;
    mCurrentControlPoint = -1;
}

AnnotationItemResizer::~AnnotationItemResizer()
{
    delete mControlPoints;
}

QRectF AnnotationItemResizer::boundingRect() const
{
    if(mAnnotationItem) {
        auto size = mControlPointSize / 2;
        return mAnnotationItem->boundingRect().adjusted(-size, -size, size, size);
    } else {
        return QRectF();
    }
}

void AnnotationItemResizer::attachTo(AbstractAnnotationItem* item)
{
    if(mAnnotationItem == nullptr) {
        grabMouse();
    }

    prepareGeometryChange();
    mAnnotationItem = item;
    mControlPoints->initPoints(item);
}

void AnnotationItemResizer::detach()
{
    if(mAnnotationItem == nullptr) {
        return;
    }

    prepareGeometryChange();
    mAnnotationItem = nullptr;
    ungrabMouse();
}

AbstractAnnotationItem * AnnotationItemResizer::attachedItem() const
{
    return mAnnotationItem;
}

void AnnotationItemResizer::grabHandle(const QPointF& pos)
{
    if(mAnnotationItem != nullptr) {
        mCurrentControlPoint = mControlPoints->indexOfPointAt(pos);
        if(mCurrentControlPoint != -1) {
            mClickOffset = pos - mControlPoints->point(mCurrentControlPoint).center();
        }
    }
}

void AnnotationItemResizer::moveHandle(const QPointF& pos)
{
    if(mAnnotationItem) {
        prepareGeometryChange();
        if(mCurrentControlPoint != -1) {
            mAnnotationItem->setPointAt(pos - mClickOffset, mCurrentControlPoint);
            mControlPoints->updatePointsPosition();
        }
    }
}

void AnnotationItemResizer::releaseHandle()
{
    mCurrentControlPoint = -1;
}

bool AnnotationItemResizer::isResizing() const
{
    return mCurrentControlPoint != -1;
}

void AnnotationItemResizer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(!mAnnotationItem) {
        return;
    }

    painter->setPen(QColor("white"));
    painter->setBrush(QColor("gray"));
    auto points = mControlPoints->points();
    for(auto point : points) {
        painter->drawRect(point);
    }
}

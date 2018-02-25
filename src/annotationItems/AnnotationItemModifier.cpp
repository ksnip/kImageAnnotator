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

#include "AnnotationItemModifier.h"

AnnotationItemModifier::AnnotationItemModifier()
{
    mControlPointSize = 10;
    mControlPoints = new ControlPoints(mControlPointSize);
    mAnnotationItem = nullptr;
    mCurrentControlPoint = -1;
}

QRectF AnnotationItemModifier::boundingRect() const
{
    if (mAnnotationItem) {
        auto size = mControlPointSize / 2;
        return mAnnotationItem->boundingRect().adjusted(-size, -size, size, size);
    } else {
        return QRectF();
    }
}

void AnnotationItemModifier::attachTo(AbstractAnnotationItem* item)
{
    if(mAnnotationItem == nullptr) {
        grabMouse();
    }

    prepareGeometryChange();
    mAnnotationItem = item;
    mControlPoints->initPoints(item);
}

void AnnotationItemModifier::detach()
{
    if (mAnnotationItem == nullptr) {
        return;
    }

    prepareGeometryChange();
    mAnnotationItem = nullptr;
    ungrabMouse();
}

void AnnotationItemModifier::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(mAnnotationItem != nullptr) {
        mCurrentControlPoint = mControlPoints->indexOfPointAt(event->scenePos());
        if(mCurrentControlPoint != -1) {
            event->accept();
        } else if(mAnnotationItem->intersects(QRectF(event->scenePos() - QPointF(1, 1), QSize(2, 2)))) {
            mCurrentControlPoint = 99;
            mClickOffset = event->scenePos() - mAnnotationItem->position();
            event->accept();
        }
    }
}

void AnnotationItemModifier::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(mCurrentControlPoint != -1) {
        prepareGeometryChange();
        if(mAnnotationItem) {
            if(mCurrentControlPoint == 99) {
                mAnnotationItem->setPosition(event->scenePos() - mClickOffset);
            } else {
                mAnnotationItem->setPointAt(event->scenePos(), mCurrentControlPoint);
            }
        }
        mControlPoints->updatePointsPosition();
    }
}

void AnnotationItemModifier::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    mCurrentControlPoint = -1;
    QGraphicsWidget::mouseReleaseEvent(event);
}

void AnnotationItemModifier::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (!mAnnotationItem) {
        return;
    }

    painter->setPen(QColor("white"));
    painter->setBrush(QColor("gray"));
    auto points = mControlPoints->points();
    for(auto point : points) {
        painter->drawRect(point);
    }
}

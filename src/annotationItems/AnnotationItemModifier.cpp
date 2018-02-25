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
    mLineItem = nullptr;
    mCurrentControlPoint = -1;
    mControlPointSize = 10;
    mControlPoints.append(QRectF(0, 0, mControlPointSize, mControlPointSize));
    mControlPoints.append(QRectF(0, 0, mControlPointSize, mControlPointSize));
}

QRectF AnnotationItemModifier::boundingRect() const
{
    if (mLineItem) {
        auto size = mControlPointSize / 2;
        return mLineItem->boundingRect().adjusted(-size, -size, size, size);
    }
}

void AnnotationItemModifier::attachTo(AbstractAnnotationLine* lineItem)
{
    if(mLineItem == nullptr) {
        grabMouse();
    }

    prepareGeometryChange();
    mLineItem = lineItem;
    updateControlPoints();
}

void AnnotationItemModifier::detach()
{
    if (mLineItem == nullptr) {
        return;
    }

    prepareGeometryChange();
    mLineItem = nullptr;
    ungrabMouse();
}

void AnnotationItemModifier::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(mLineItem != nullptr) {
        mCurrentControlPoint = controlPointAt(event->scenePos());
        if(mCurrentControlPoint != -1) {
            event->accept();
        } else if(mLineItem->intersects(QRectF(event->scenePos() - QPointF(1, 1), QSize(2, 2)))) {
            mCurrentControlPoint = 99;
            mClickOffset = event->scenePos() - mLineItem->position();
            event->accept();
        }
    }
}

void AnnotationItemModifier::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(mCurrentControlPoint != -1) {
        prepareGeometryChange();
        if(mCurrentControlPoint == 0 || mCurrentControlPoint == 1) {
            mLineItem->setPointAt(event->scenePos(), mCurrentControlPoint);
        } else if (mCurrentControlPoint == 99) {
            mLineItem->setPosition(event->scenePos() - mClickOffset);
        }
        updateControlPoints();
    }
}

void AnnotationItemModifier::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    mCurrentControlPoint = -1;
    QGraphicsWidget::mouseReleaseEvent(event);
}

void AnnotationItemModifier::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (mLineItem != nullptr) {
        painter->setPen(QColor("white"));
        painter->setBrush(QColor("gray"));
        painter->drawRect(mControlPoints[0]);
        painter->drawRect(mControlPoints[1]);
    }
}

void AnnotationItemModifier::updateControlPoints()
{
    if(mLineItem != nullptr) {
        auto line = mLineItem->line();
        mControlPoints[0].moveCenter(line.p1());
        mControlPoints[1].moveCenter(line.p2());
    }
}

int AnnotationItemModifier::controlPointAt(const QPointF& point) const
{
    for(auto controlPoint : mControlPoints) {
        if(controlPoint.contains(point)) {
            return mControlPoints.indexOf(controlPoint);
        }
    }
    return -1;
}

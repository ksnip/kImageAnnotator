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
    mControlPoints.append(QRectF(0,0,mControlPointSize,mControlPointSize));
    mControlPoints.append(QRectF(0,0,mControlPointSize,mControlPointSize));
}

QRectF AnnotationItemModifier::boundingRect() const
{
    if (mLineItem) {
        return mLineItem->boundingRect().adjusted(-mControlPointSize, -mControlPointSize, mControlPointSize, mControlPointSize);
    }
}

void AnnotationItemModifier::attachTo(AbstractAnnotationLine* lineItem)
{
    prepareGeometryChange();
    mLineItem = lineItem;
    updateControlPoints();

    // Without this we don't get mouse input
    grabMouse();
}

void AnnotationItemModifier::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(mLineItem != nullptr) {
        if(mControlPoints[0].contains(event->scenePos())) {
            mCurrentControlPoint = 0;
            return;
        } else if (mControlPoints[1].contains(event->scenePos())) {
            mCurrentControlPoint = 1;
            return;
        }
    }
    QGraphicsWidget::mousePressEvent(event);
}

void AnnotationItemModifier::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(mCurrentControlPoint != -1) {
        prepareGeometryChange();
        if(mCurrentControlPoint == 0) {
            mLineItem->setP1(event->scenePos());
        } else if (mCurrentControlPoint == 1) {
            mLineItem->setP2(event->scenePos());
        }
        updateControlPoints();
    }
    QGraphicsWidget::mouseMoveEvent(event);
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

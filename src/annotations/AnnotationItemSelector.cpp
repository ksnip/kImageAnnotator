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

#include "AnnotationItemSelector.h"

AnnotationItemSelector::AnnotationItemSelector()
{
    
}

QRectF AnnotationItemSelector::boundingRect() const
{
    return mSelectionRect.normalized();
}

void AnnotationItemSelector::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() != Qt::LeftButton) {
        return;
    }

    initSelectionRectAt(event->scenePos());
}

void AnnotationItemSelector::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->buttons() != Qt::LeftButton) {
        return;
    }
    updateSelectionRect(event->scenePos());
}

void AnnotationItemSelector::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() != Qt::LeftButton) {
        return;
    }
}

void AnnotationItemSelector::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::darkBlue);
    painter->setBrush(QColor(0, 0, 255, 60));
    painter->drawRect(mSelectionRect);
}

void AnnotationItemSelector::initSelectionRectAt(const QPointF& position)
{
    prepareGeometryChange();
    mSelectionRect.setTopLeft(position);
    updateSelectionRect(position);
}

void AnnotationItemSelector::updateSelectionRect(const QPointF& position)
{
    prepareGeometryChange();
    mSelectionRect.setBottomRight(position);
}

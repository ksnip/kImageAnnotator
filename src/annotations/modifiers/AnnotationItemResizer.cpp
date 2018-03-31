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
    mResizeHandleSize = 10;
    mResizeHandles = new ResizeHandles(mResizeHandleSize);
    mAnnotationItem = nullptr;
    mCurrentControlPoint = -1;
}

AnnotationItemResizer::~AnnotationItemResizer()
{
    delete mResizeHandles;
}

QRectF AnnotationItemResizer::boundingRect() const
{
    if(mAnnotationItem) {
        auto size = mResizeHandleSize / 2;
        return mAnnotationItem->boundingRect().adjusted(-size, -size, size, size);
    } else {
        return QRectF();
    }
}

void AnnotationItemResizer::attachTo(AbstractAnnotationItem* item)
{
    prepareGeometryChange();
    mAnnotationItem = item;
    mResizeHandles->initHandles(item);
    installParentEventFilter();
}

void AnnotationItemResizer::detach()
{
    prepareGeometryChange();
    mAnnotationItem = nullptr;
    removeParentEventFilter();
}

AbstractAnnotationItem* AnnotationItemResizer::attachedItem() const
{
    return mAnnotationItem;
}

void AnnotationItemResizer::grabHandle(const QPointF& pos)
{
    if(mAnnotationItem == nullptr) {
        return;
    }

    mCurrentControlPoint = mResizeHandles->indexOfHandleAt(pos);
    if(mCurrentControlPoint != -1) {
        mClickOffset = pos - mResizeHandles->handle(mCurrentControlPoint).center();
    }
}

void AnnotationItemResizer::moveHandle(const QPointF& pos)
{
    if(mAnnotationItem == nullptr) {
        return;
    }

    if(mCurrentControlPoint != -1) {
        mAnnotationItem->setPointAt(pos - mClickOffset, mCurrentControlPoint);
        refresh();
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

void AnnotationItemResizer::refresh()
{
    if(mAnnotationItem == nullptr) {
        return;
    }

    prepareGeometryChange();
    mResizeHandles->updateHandlesPosition();
}

bool AnnotationItemResizer::sceneEventFilter(QGraphicsItem* watched, QEvent* event)
{
    Q_UNUSED(watched)

    if(event->type() == QEvent::GraphicsSceneHoverMove) {
        auto hoverMoveEvent = dynamic_cast<QGraphicsSceneHoverEvent*>(event);
        updateParentCursor(hoverMoveEvent->scenePos());
        return false;
    }
    return true;
}

void AnnotationItemResizer::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(mAnnotationItem == nullptr) {
        return;
    }

    painter->setPen(Qt::white);
    painter->setBrush(Qt::gray);
    auto points = mResizeHandles->handles();
    for(auto point : points) {
        painter->drawRect(point);
    }
}

void AnnotationItemResizer::installParentEventFilter()
{
    auto parent = parentItem();
    if(parent != nullptr) {
        parent->installSceneEventFilter(this);
    }
}

void AnnotationItemResizer::removeParentEventFilter()
{
    auto parent = parentItem();
    if(parent != nullptr) {
        parent->removeSceneEventFilter(this);
    }
}

void AnnotationItemResizer::updateParentCursor(const QPointF& pos)
{
    auto parent = parentItem();
    if(parent == nullptr) {
        return;
    }

    auto cursor = mResizeHandles->getCursorForHandle(pos);
    if(parent->cursor().shape() == cursor) {
        return;
    }

    parent->setCursor(cursor);
}

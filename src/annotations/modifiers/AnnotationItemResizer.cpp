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

#include "AnnotationItemResizer.h"

namespace kImageAnnotator {

AnnotationItemResizer::AnnotationItemResizer(AbstractAnnotationItem *item)
{
    mAnnotationItem = item;
    mCurrentHandle = -1;
    mResizeHandles = ResizeHandlesFactory::createResizeHandles(item);
    prepareGeometryChange();
}

AnnotationItemResizer::~AnnotationItemResizer()
{
    mAnnotationItem = nullptr;
    delete mResizeHandles;
}

QRectF AnnotationItemResizer::boundingRect() const
{
    auto size = mResizeHandles->handleSize() / 2;
    return mAnnotationItem->boundingRect().normalized().adjusted(-size, -size, size, size);
}

void AnnotationItemResizer::grabHandle(const QPointF &pos)
{
    mCurrentHandle = mResizeHandles->indexOfHandleAt(pos);
    if (mCurrentHandle != -1) {
        mClickOffset = pos - mResizeHandles->handle(mCurrentHandle).anchor();
    }
}

void AnnotationItemResizer::moveHandle(const QPointF &pos)
{
    if (mCurrentHandle != -1) {
        emit newCommand(new ResizeCommand(mAnnotationItem, mCurrentHandle, pos - mClickOffset));
    }
}

void AnnotationItemResizer::releaseHandle()
{
    mCurrentHandle = -1;
}

bool AnnotationItemResizer::isResizing() const
{
    return mCurrentHandle != -1;
}

void AnnotationItemResizer::refresh()
{
    prepareGeometryChange();
    mResizeHandles->update();
}

bool AnnotationItemResizer::isItemVisible() const
{
    return mAnnotationItem != nullptr && mAnnotationItem->isVisible();
}

Qt::CursorShape AnnotationItemResizer::cursorForPos(const QPointF &pos)
{
    return mResizeHandles->cursorForPos(pos);
}

Qt::CursorShape AnnotationItemResizer::cursorForCurrentHandle()
{
    return mResizeHandles->cursorForHandle(mCurrentHandle);
}

void AnnotationItemResizer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::white);
    painter->setBrush(Qt::gray);
    auto points = mResizeHandles->handles();
    for (auto point : points) {
        painter->drawRect(point);
    }
}

} // namespace kImageAnnotator

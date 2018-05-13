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

#include "AbstractItemResizeHandles.h"

AbstractItemResizeHandles::AbstractItemResizeHandles()
{
    mHandleSize = 10;
}

int AbstractItemResizeHandles::indexOfHandleAt(const QPointF &pos) const
{
    for (auto handle : mHandles) {
        if (handle.contains(pos)) {
            return mHandles.indexOf(handle);
        }
    }
    return -1;
}

QRectF AbstractItemResizeHandles::handle(int index) const
{
    if (index < 0 || index >= mHandles.count()) {
        return QRectF();
    }

    return mHandles[index];
}

QList<QRectF> AbstractItemResizeHandles::handles() const
{
    return mHandles;
}

Qt::CursorShape AbstractItemResizeHandles::cursorForPos(const QPointF &pos) const
{
    auto index = indexOfHandleAt(pos);
    return cursorForHandle(index);
}

Qt::CursorShape AbstractItemResizeHandles::cursorForHandle(int index) const
{
    if (index == -1 || mCursors.isEmpty()) {
        return CursorHelper::defaultCursor();
    }

    return mCursors[index];
}

void AbstractItemResizeHandles::initHandles(int count)
{
    mHandles.clear();
    for (auto i = 0; i < count; i++) {
        mHandles.append(QRectF(0, 0, mHandleSize, mHandleSize));
    }
}

int AbstractItemResizeHandles::handleSize() const
{
    return mHandleSize;
}

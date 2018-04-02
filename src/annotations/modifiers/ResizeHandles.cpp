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

#include "ResizeHandles.h"

ResizeHandles::ResizeHandles(int ResizeHandles)
{
    mHandleSize = ResizeHandles;
    mLineItem = nullptr;
    mRectItem = nullptr;
}

void ResizeHandles::initHandles(AbstractAnnotationItem* item)
{
    mLineItem = dynamic_cast<AbstractAnnotationLine*>(item);
    mRectItem = dynamic_cast<AbstractAnnotationRect*>(item);
    mHandles.clear();
    if(mLineItem) {
        addHandlesToList(2);
        addLineCursorsToList();
    } else if(mRectItem) {
        addHandlesToList(8);
        addRectCursorsToList();
    }
    updateHandlesPosition();
}

void ResizeHandles::updateHandlesPosition()
{
    if(mLineItem) {
        auto line = mLineItem->line();
        mHandles[0].moveCenter(line.p1());
        mHandles[1].moveCenter(line.p2());
    } else if(mRectItem) {
        auto rect = mRectItem->rect();
        mHandles[0].moveCenter(rect.topLeft());
        mHandles[1].moveCenter(QPointF(rect.center().x(), rect.top()));
        mHandles[2].moveCenter(rect.topRight());
        mHandles[3].moveCenter(QPointF(rect.right(), rect.center().y()));
        mHandles[4].moveCenter(rect.bottomRight());
        mHandles[5].moveCenter(QPointF(rect.center().x(), rect.bottom()));
        mHandles[6].moveCenter(rect.bottomLeft());
        mHandles[7].moveCenter(QPointF(rect.left(), rect.center().y()));
    }
}

int ResizeHandles::indexOfHandleAt(const QPointF& pos) const
{
    for(auto handle : mHandles) {
        if(handle.contains(pos)) {
            return mHandles.indexOf(handle);
        }
    }
    return -1;
}

QList<QRectF> ResizeHandles::handles() const
{
    return mHandles;
}

QRectF ResizeHandles::handle(int index) const
{
    if(index < 0 || index >= mHandles.count()) {
        return QRectF();
    }

    return mHandles[index];
}

Qt::CursorShape ResizeHandles::getCursorForHandle(const QPointF& pos) const
{
    auto index = indexOfHandleAt(pos);

    if(index == -1 || mCursors.isEmpty()) {
        return CursorHelper::defaultCursor();
    }

    return mCursors[index];
}

void ResizeHandles::addHandlesToList(int count)
{
    for(auto i = 0; i < count; i++) {
        mHandles.append(QRectF(0, 0, mHandleSize, mHandleSize));
    }
}

void ResizeHandles::addLineCursorsToList()
{
    mCursors.clear();
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::allResizeCursor());
}

void ResizeHandles::addRectCursorsToList()
{
    mCursors.clear();
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::verticalResizeCursor());
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::horizontalResizeCursor());
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::verticalResizeCursor());
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::horizontalResizeCursor());
}

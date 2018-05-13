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

#include "RectResizeHandles.h"

RectResizeHandles::RectResizeHandles(AbstractAnnotationRect *rectItem)
{
    mRectItem = rectItem;
    initHandles(8);
    initCursors();
    update();
}

void RectResizeHandles::update()
{
    auto rect = mRectItem->rect();
    mHandles[0].moveCenter(rect.topLeft());
    mHandles[1].moveCenter(QPointF(rect.center().x(), rect.top()));
    mHandles[2].moveCenter(rect.topRight());
    mHandles[3].moveCenter(QPointF(rect.right(), rect.center().y()));
    mHandles[4].moveCenter(rect.bottomRight());
    mHandles[5].moveCenter(QPointF(rect.center().x(), rect.bottom()));
    mHandles[6].moveCenter(rect.bottomLeft());
    mHandles[7].moveCenter(QPointF(rect.left(), rect.center().y()));

    updateRectCursors();
}

void RectResizeHandles::initCursors()
{
    mCursors.clear();
    mCursors.append(CursorHelper::fDiagResizeCursor());
    mCursors.append(CursorHelper::verticalResizeCursor());
    mCursors.append(CursorHelper::bDiagResizeCursor());
    mCursors.append(CursorHelper::horizontalResizeCursor());
    mCursors.append(CursorHelper::fDiagResizeCursor());
    mCursors.append(CursorHelper::verticalResizeCursor());
    mCursors.append(CursorHelper::bDiagResizeCursor());
    mCursors.append(CursorHelper::horizontalResizeCursor());
}

void RectResizeHandles::updateRectCursors()
{
    if (mRectItem == nullptr || mCursors.isEmpty()) {
        return;
    }

    auto rect = mRectItem->rect().normalized();
    mCursors[indexOfHandleAt(rect.topLeft())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleAt(rect.topRight())] = CursorHelper::bDiagResizeCursor();
    mCursors[indexOfHandleAt(rect.bottomRight())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleAt(rect.bottomLeft())] = CursorHelper::bDiagResizeCursor();
}

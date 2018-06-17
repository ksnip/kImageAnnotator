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

#include "PathResizeHandles.h"

PathResizeHandles::PathResizeHandles(AbstractAnnotationPath *pathItem)
{
    mPathItem = pathItem;
    initHandles(8);
    initCursors();
    update();
}

void PathResizeHandles::update()
{
    auto rect = mPathItem->boundingRect();
    auto offset = mPathItem->properties().size() / 2;
    mHandles[0].moveCenter(ShapeHelper::rectTopLeftWithOffset(rect, offset));
    mHandles[0].setAnchor(rect.topLeft());
    mHandles[1].moveCenter(ShapeHelper::rectTopWithOffset(rect, offset));
    mHandles[1].setAnchor(ShapeHelper::rectTop(rect));
    mHandles[2].moveCenter(ShapeHelper::rectTopRightWithOffset(rect, offset));
    mHandles[2].setAnchor(rect.topRight());
    mHandles[3].moveCenter(ShapeHelper::rectRightWithOffset(rect, offset));
    mHandles[3].setAnchor(ShapeHelper::rectRight(rect));
    mHandles[4].moveCenter(ShapeHelper::rectBottomRightWithOffset(rect, offset));
    mHandles[4].setAnchor(rect.bottomRight());
    mHandles[5].moveCenter(ShapeHelper::rectBottomWithOffset(rect, offset));
    mHandles[5].setAnchor(ShapeHelper::rectBottom(rect));
    mHandles[6].moveCenter(ShapeHelper::rectBottomLeftWithOffset(rect, offset));
    mHandles[6].setAnchor(rect.bottomLeft());
    mHandles[7].moveCenter(ShapeHelper::rectLeftWithOffset(rect, offset));
    mHandles[7].setAnchor(ShapeHelper::rectLeft(rect));

    updateRectCursors();
}

void PathResizeHandles::initCursors()
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

void PathResizeHandles::updateRectCursors()
{
    if (mPathItem == nullptr || mCursors.isEmpty()) {
        return;
    }

    auto rect = mPathItem->boundingRect().normalized();
    mCursors[indexOfHandleWithAnchorAt(rect.topLeft())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.topRight())] = CursorHelper::bDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.bottomRight())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.bottomLeft())] = CursorHelper::bDiagResizeCursor();
}

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

#include "AbstractRectResizeHandles.h"

namespace kImageAnnotator {

void AbstractRectResizeHandles::update()
{
    auto rect = getRect();
    auto offset = getOffset();
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

void AbstractRectResizeHandles::initCursors()
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

void AbstractRectResizeHandles::updateRectCursors()
{
    if (mCursors.isEmpty()) {
        return;
    }

    auto rect = getItemBoundingRect();
    mCursors[indexOfHandleWithAnchorAt(rect.topLeft())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.topRight())] = CursorHelper::bDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.bottomRight())] = CursorHelper::fDiagResizeCursor();
    mCursors[indexOfHandleWithAnchorAt(rect.bottomLeft())] = CursorHelper::bDiagResizeCursor();
}

} // namespace kImageAnnotator

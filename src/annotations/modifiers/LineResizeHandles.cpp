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

#include "LineResizeHandles.h"

LineResizeHandles::LineResizeHandles(AbstractAnnotationLine *lineItem)
{
    mLineItem = lineItem;
    initHandles(2);
    initCursors();
    update();
}

void LineResizeHandles::update()
{
    auto line = mLineItem->line();
    mHandles[0].moveCenter(QPointF(line.p1().x(), line.p1().y()));
    mHandles[1].moveCenter(line.p2());
}

void LineResizeHandles::initCursors()
{
    mCursors.clear();
    mCursors.append(CursorHelper::allResizeCursor());
    mCursors.append(CursorHelper::allResizeCursor());
}

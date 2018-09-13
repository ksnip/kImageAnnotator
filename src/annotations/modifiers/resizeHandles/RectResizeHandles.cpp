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

namespace kImageAnnotator {

RectResizeHandles::RectResizeHandles(AbstractAnnotationRect *rectItem)
{
    mRectItem = rectItem;
    initHandles(8);
    initCursors();
    update();
}

QRectF RectResizeHandles::getRect() const
{
    return mRectItem->rect();
}

int RectResizeHandles::getOffset() const
{
    return mRectItem->properties().size() / 2;
}

QRectF RectResizeHandles::getItemBoundingRect() const
{
    return mRectItem->rect().normalized();
}

} // namespace kImageAnnotator

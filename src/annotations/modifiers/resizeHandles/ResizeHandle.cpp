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

#include "ResizeHandle.h"

namespace kImageAnnotator {

double ResizeHandle::mDefaultHandleSize = 10.0;

ResizeHandle::ResizeHandle(double zoomValue)
    : QRectF(0, 0, mDefaultHandleSize / zoomValue, mDefaultHandleSize / zoomValue)
{
}

QPointF ResizeHandle::anchor() const
{
    return center() + mOffset;
}

void ResizeHandle::setAnchor(const QPointF &pos)
{
    mOffset = pos - center();
}

void ResizeHandle::applyZoomValue(double value)
{
    const auto offset = 0.5 * (handleSize() - mDefaultHandleSize / value);
    adjust(offset, offset, -offset, -offset);
}

double ResizeHandle::handleSize() const
{
    return width();
}

} // namespace kImageAnnotator

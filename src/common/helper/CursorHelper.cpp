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

#include "CursorHelper.h"

namespace kImageAnnotator {

Qt::CursorShape CursorHelper::defaultCursor()
{
    return Qt::ArrowCursor;
}

Qt::CursorShape CursorHelper::allResizeCursor()
{
    return Qt::SizeAllCursor;
}

Qt::CursorShape CursorHelper::horizontalResizeCursor()
{
    return Qt::SizeHorCursor;
}

Qt::CursorShape CursorHelper::verticalResizeCursor()
{
    return Qt::SizeVerCursor;
}

Qt::CursorShape CursorHelper::bDiagResizeCursor()
{
    return Qt::SizeBDiagCursor;
}

Qt::CursorShape CursorHelper::fDiagResizeCursor()
{
    return Qt::SizeFDiagCursor;
}

Qt::CursorShape CursorHelper::movableCursor()
{
    return Qt::OpenHandCursor;
}

Qt::CursorShape CursorHelper::movingCursor()
{
    return Qt::ClosedHandCursor;
}

} // namespace kImageAnnotator
/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "PointerRectResizeHandles.h"

namespace kImageAnnotator {

PointerRectResizeHandles::PointerRectResizeHandles(AbstractAnnotationPointerRect *pointerRectItem, double zoomValue) :
	RectResizeHandles(pointerRectItem, zoomValue),
	mPointerRectItem(pointerRectItem)
{
	initHandles(9, zoomValue);
	initCursors();
	update();
}

void PointerRectResizeHandles::update()
{
	RectResizeHandles::update();
	mHandles[8].moveCenter(mPointerRectItem->pointAt(8));
	mHandles[8].setAnchor(mPointerRectItem->pointAt(8));
}

void PointerRectResizeHandles::initCursors()
{
	RectResizeHandles::initCursors();
	mCursors.append(CursorHelper::allResizeCursor());
}

} // namespace kImageAnnotator
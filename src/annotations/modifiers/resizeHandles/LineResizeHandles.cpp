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

#include "LineResizeHandles.h"

namespace kImageAnnotator {

LineResizeHandles::LineResizeHandles(AbstractAnnotationLine *lineItem, double zoomValue)
{
	mLineItem = lineItem;
	initHandles(2, zoomValue);
	initCursors();
	update();
}

void LineResizeHandles::update()
{
	auto line = mLineItem->line();
	auto offset = mLineItem->properties()->width();
	auto outerLine = ShapeHelper::extendLine(line, offset);
	mHandles[0].moveCenter(QPointF(outerLine.p1().x(), outerLine.p1().y()));
	mHandles[0].setAnchor(line.p1());
	mHandles[1].moveCenter(QPointF(outerLine.p2().x(), outerLine.p2().y()));
	mHandles[1].setAnchor(line.p2());
}

void LineResizeHandles::initCursors()
{
	mCursors.clear();
	mCursors.append(CursorHelper::allResizeCursor());
	mCursors.append(CursorHelper::allResizeCursor());
}

} // namespace kImageAnnotator

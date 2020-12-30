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

#include "SelectionHandles.h"

namespace kImageAnnotator {

SelectionHandles::SelectionHandles() : mGrabbedIndex(-1)
{
	for (auto i = 0; i < 8; i++) {
		mHandles.append(QRectF(0, 0, Constants::ResizeHandleSize, Constants::ResizeHandleSize));
	}
}

QVector<QRectF> SelectionHandles::handles() const
{
	return mHandles;
}

void SelectionHandles::grabHandle(const QPointF &position, const QRectF &selection)
{
	for (auto handle : mHandles) {
		if (handle.contains(position)) {
			mGrabbedIndex = mHandles.indexOf(handle);
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(selection, mGrabbedIndex);
			return;
		}
	}
	mGrabbedIndex = -1;
}

void SelectionHandles::releaseHandle()
{
	mGrabbedIndex = -1;
}

int SelectionHandles::grabbedIndex() const
{
	return mGrabbedIndex;
}

void SelectionHandles::updateHandles(const QRectF &selection)
{
	auto rectSize = Constants::ResizeHandleSize / 2;
	mHandles[0].moveTopLeft(ShapeHelper::rectTopLeftWithOffset(selection, 0).toPoint());
	mHandles[1].moveCenter(ShapeHelper::rectTopWithOffset(selection, -rectSize).toPoint());
	mHandles[2].moveTopRight(ShapeHelper::rectTopRightWithOffset(selection, 0).toPoint());
	mHandles[3].moveCenter(ShapeHelper::rectRightWithOffset(selection, -rectSize).toPoint());
	mHandles[4].moveBottomRight(ShapeHelper::rectBottomRightWithOffset(selection, 0).toPoint());
	mHandles[5].moveCenter(ShapeHelper::rectBottomWithOffset(selection, -rectSize).toPoint());
	mHandles[6].moveBottomLeft(ShapeHelper::rectBottomLeftWithOffset(selection, 0).toPoint());
	mHandles[7].moveCenter(ShapeHelper::rectLeftWithOffset(selection, -rectSize).toPoint());
}

bool SelectionHandles::isHandleGrabbed() const
{
	return mGrabbedIndex != -1;
}

QPointF SelectionHandles::grabOffset() const
{
	return mGrabOffset;
}

} // namespace kImageAnnotator

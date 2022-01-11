/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#include "SelectionHandlesHorizontal.h"

namespace kImageAnnotator {


SelectionHandlesHorizontal::SelectionHandlesHorizontal() :
	mGrabbedIndex(-1),
	mHandleSize(ScaledSizeProvider::resizeHandleSize())
{
	mHandles[3] = QRectF(0, 0, mHandleSize, mHandleSize);
	mHandles[7] = QRectF(0, 0, mHandleSize, mHandleSize);
}

QVector<QRectF> SelectionHandlesHorizontal::handles() const
{
	return mHandles.values().toVector();
}

void SelectionHandlesHorizontal::grabHandle(const QPointF &position, const QRectF &selection)
{
	for (auto index : mHandles.keys()) {
		auto handle = mHandles[index];
		if (handle.contains(position)) {
			mGrabbedIndex = index;
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(selection, mGrabbedIndex);
			return;
		}
	}
	mGrabbedIndex = -1;
}

void SelectionHandlesHorizontal::releaseHandle()
{
	mGrabbedIndex = -1;
}

int SelectionHandlesHorizontal::grabbedIndex() const
{
	return mGrabbedIndex;
}

void SelectionHandlesHorizontal::updateHandles(const QRectF &selection)
{
	auto offset = mHandleSize * 0.5;
	mHandles[3].moveCenter(ShapeHelper::rectRightWithOffset(selection, -offset).toPoint());
	mHandles[7].moveCenter(ShapeHelper::rectLeftWithOffset(selection, -offset).toPoint());
}

bool SelectionHandlesHorizontal::isHandleGrabbed() const
{
	return mGrabbedIndex != -1;
}

QPointF SelectionHandlesHorizontal::grabOffset() const
{
	return mGrabOffset;
}

void SelectionHandlesHorizontal::applyZoomValue(double value)
{
	auto oldHandleSize = mHandleSize;
	mHandleSize = ScaledSizeProvider::resizeHandleSize() / value;
	auto offset = 0.5 * (oldHandleSize - mHandleSize);

	for (auto &handle : mHandles) {
		handle.adjust(offset, offset, -offset, -offset);
	}
}

} // namespace kImageAnnotator

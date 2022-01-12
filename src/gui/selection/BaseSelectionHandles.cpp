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

#include "BaseSelectionHandles.h"

namespace kImageAnnotator {

BaseSelectionHandles::BaseSelectionHandles() :
	mGrabbedIndex(-1),
	mHandleSize(ScaledSizeProvider::resizeHandleSize())
{
}

QList<QRectF> BaseSelectionHandles::handles() const
{
	return mIndexToHandleMap.values();
}

void BaseSelectionHandles::grabHandle(const QPointF &position, const QRectF &selection)
{
	for (auto entry : mIndexToHandleMap.toStdMap()) {
		auto index = entry.first;
		auto handle = entry.second;

		if (handle.contains(position)) {
			mGrabbedIndex = index;
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(selection, mGrabbedIndex);
			return;
		}
	}

	mGrabbedIndex = -1;
}

void BaseSelectionHandles::releaseHandle()
{
	mGrabbedIndex = -1;
}

int BaseSelectionHandles::grabbedIndex() const
{
	return mGrabbedIndex;
}

void BaseSelectionHandles::updateHandles(const QRectF &selection)
{
	auto offset = mHandleSize * 0.5;
	if (mIndexToHandleMap.contains(0)) {
		mIndexToHandleMap[0].moveTopLeft(ShapeHelper::rectTopLeftWithOffset(selection, 0).toPoint());
	}

	if(mIndexToHandleMap.contains(1)) {
		mIndexToHandleMap[1].moveCenter(ShapeHelper::rectTopWithOffset(selection, -offset).toPoint());
	}

	if(mIndexToHandleMap.contains(2)) {
		mIndexToHandleMap[2].moveTopRight(ShapeHelper::rectTopRightWithOffset(selection, 0).toPoint());
	}

	if(mIndexToHandleMap.contains(3)) {
		mIndexToHandleMap[3].moveCenter(ShapeHelper::rectRightWithOffset(selection, -offset).toPoint());
	}

	if(mIndexToHandleMap.contains(4)) {
		mIndexToHandleMap[4].moveBottomRight(ShapeHelper::rectBottomRightWithOffset(selection, 0).toPoint());
	}

	if(mIndexToHandleMap.contains(5)) {
		mIndexToHandleMap[5].moveCenter(ShapeHelper::rectBottomWithOffset(selection, -offset).toPoint());
	}

	if(mIndexToHandleMap.contains(6)) {
		mIndexToHandleMap[6].moveBottomLeft(ShapeHelper::rectBottomLeftWithOffset(selection, 0).toPoint());
	}

	if(mIndexToHandleMap.contains(7)) {
		mIndexToHandleMap[7].moveCenter(ShapeHelper::rectLeftWithOffset(selection, -offset).toPoint());
	}
}

bool BaseSelectionHandles::isHandleGrabbed() const
{
	return mGrabbedIndex != -1;
}

QPointF BaseSelectionHandles::grabOffset() const
{
	return mGrabOffset;
}

void BaseSelectionHandles::applyZoomValue(double value)
{
	auto oldHandleSize = mHandleSize;
	mHandleSize = ScaledSizeProvider::resizeHandleSize() / value;
	auto offset = 0.5 * (oldHandleSize - mHandleSize);

	for (auto &handle : mIndexToHandleMap) {
		handle.adjust(offset, offset, -offset, -offset);
	}
}

void BaseSelectionHandles::insertHandle(int index)
{
	mIndexToHandleMap[index] = QRectF(0, 0, mHandleSize, mHandleSize);
}

} // namespace kImageAnnotator

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

#include "CropHandles.h"

namespace kImageAnnotator {

CropHandles::CropHandles() : mGrabbedIndex(-1)
{
	for (auto i = 0; i < 8; i++) {
		mHandles.append(QRectF(0, 0, Constants::ResizeHandleSize, Constants::ResizeHandleSize));
	}
}

QVector<QRectF> CropHandles::handles() const
{
	return mHandles;
}

void CropHandles::grabHandle(const QPointF &position, const QRectF &rect)
{
	for (auto handle : mHandles) {
		if (handle.contains(position)) {
			mGrabbedIndex = mHandles.indexOf(handle);
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(rect, mGrabbedIndex);
			return;
		}
	}
	mGrabbedIndex = -1;
}

void CropHandles::releaseHandle()
{
	mGrabbedIndex = -1;
}

int CropHandles::grabbedIndex() const
{
	return mGrabbedIndex;
}

void CropHandles::updateHandles(const QRectF &rect)
{
	auto rectSize = Constants::ResizeHandleSize / 2;
	mHandles[0].moveTopLeft(ShapeHelper::rectTopLeftWithOffset(rect, 0).toPoint());
	mHandles[1].moveCenter(ShapeHelper::rectTopWithOffset(rect, -rectSize).toPoint());
	mHandles[2].moveTopRight(ShapeHelper::rectTopRightWithOffset(rect, 0).toPoint());
	mHandles[3].moveCenter(ShapeHelper::rectRightWithOffset(rect, -rectSize).toPoint());
	mHandles[4].moveBottomRight(ShapeHelper::rectBottomRightWithOffset(rect, 0).toPoint());
	mHandles[5].moveCenter(ShapeHelper::rectBottomWithOffset(rect, -rectSize).toPoint());
	mHandles[6].moveBottomLeft(ShapeHelper::rectBottomLeftWithOffset(rect, 0).toPoint());
	mHandles[7].moveCenter(ShapeHelper::rectLeftWithOffset(rect, -rectSize).toPoint());
}

bool CropHandles::isHandleGrabbed() const
{
	return mGrabbedIndex != -1;
}

QPointF CropHandles::grabOffset() const
{
	return mGrabOffset;
}

} // namespace kImageAnnotator

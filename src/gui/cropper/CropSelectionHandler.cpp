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

#include "CropSelectionHandler.h"

namespace kImageAnnotator {

CropSelectionHandler::CropSelectionHandler(AnnotationArea *annotationArea) : mAnnotationArea(annotationArea),
                                                                             mIsResizing(false),
                                                                             mGrabbedHandleIndex(-1)
{
	for (auto i = 0; i < 8; i++) {
		mSelectionHandles.append(QRectF(0, 0, Constants::ResizeHandleSize, Constants::ResizeHandleSize));
	}
}

QRectF CropSelectionHandler::selection() const
{
	return mSelection;
}

QVector<QRectF> CropSelectionHandler::selectionHandles() const
{
	return mSelectionHandles;
}

void CropSelectionHandler::grabHandle(const QPoint &position)
{
	for (auto handle : mSelectionHandles) {
		if (handle.contains(position)) {
			mGrabbedHandleIndex = mSelectionHandles.indexOf(handle);
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(mSelection, mGrabbedHandleIndex);
			break;
		}
	}
	mIsResizing = true;
	update();
}

void CropSelectionHandler::moveHandle(const QPoint &position)
{
	if (mGrabbedHandleIndex != -1) {
		auto newSelection = ShapeHelper::setRectPointAtIndex(mSelection, mGrabbedHandleIndex, position - mGrabOffset);
		mSelection = trimToViewPort(newSelection);
		update();
	}
}

void CropSelectionHandler::releaseHandle()
{
	if (mIsResizing) {
		mGrabbedHandleIndex = -1;
		mIsResizing = false;
		update();
	}
}

void CropSelectionHandler::resetSelection()
{
	mSelection = mAnnotationArea->sceneRect();
	mMaxSelectionSize = mAnnotationArea->sceneRect();
	update();
}

bool CropSelectionHandler::isResizing() const
{
	return mIsResizing;
}

void CropSelectionHandler::setWidth(int width)
{
	if ((mSelection.x() + width) <= mMaxSelectionSize.width()) {
		mSelection.setWidth(width);
	} else {
		mSelection.setWidth(mMaxSelectionSize.width() - mSelection.x());
	}
	update();
}

void CropSelectionHandler::setHeight(int height)
{
	if ((mSelection.y() + height) <= mMaxSelectionSize.height()) {
		mSelection.setHeight(height);
	} else {
		mSelection.setHeight(mMaxSelectionSize.height() - mSelection.y());
	}
	update();
}

void CropSelectionHandler::setPositionX(int x)
{
	if ((x + mSelection.width()) <= mMaxSelectionSize.width()) {
		mSelection.moveTo(x, mSelection.y());
	} else {
		mSelection.moveTo(mMaxSelectionSize.width() - mSelection.width(), mSelection.y());
	}
	update();
}

void CropSelectionHandler::setPositionY(int y)
{
	if ((y + mSelection.height()) <= mMaxSelectionSize.height()) {
		mSelection.moveTo(mSelection.x(), y);
	} else {
		mSelection.moveTo(mSelection.x(), mMaxSelectionSize.height() - mSelection.height());
	}
	update();
}

void CropSelectionHandler::update()
{
	updateHandles();
	mAnnotationArea->update();
	notifyAboutChanged();
}

void CropSelectionHandler::notifyAboutChanged() const
{
	emit selectionChanged(mSelection);
}

void CropSelectionHandler::updateHandles()
{
	auto rectSize = Constants::ResizeHandleSize / 2;
	mSelectionHandles[0].moveTopLeft(ShapeHelper::rectTopLeftWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[1].moveCenter(ShapeHelper::rectTopWithOffset(mSelection, -rectSize).toPoint());
	mSelectionHandles[2].moveTopRight(ShapeHelper::rectTopRightWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[3].moveCenter(ShapeHelper::rectRightWithOffset(mSelection, -rectSize).toPoint());
	mSelectionHandles[4].moveBottomRight(ShapeHelper::rectBottomRightWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[5].moveCenter(ShapeHelper::rectBottomWithOffset(mSelection, -rectSize).toPoint());
	mSelectionHandles[6].moveBottomLeft(ShapeHelper::rectBottomLeftWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[7].moveCenter(ShapeHelper::rectLeftWithOffset(mSelection, -rectSize).toPoint());
}

QRectF &CropSelectionHandler::trimToViewPort(QRectF &rect) const
{
	if (rect.x() < 0) {
		rect.setX(0);
	}

	if (rect.y() < 0) {
		rect.setY(0);
	}

	if (rect.width() < 0) {
		rect.setWidth(0);
		rect.moveLeft(mSelection.left());
	}

	if (rect.height() < 0) {
		rect.setHeight(0);
		rect.moveTop(mSelection.top());
	}

	if (rect.x() + rect.width() > mMaxSelectionSize.width()) {
		rect.setWidth(mMaxSelectionSize.width() - rect.x());
	}

	if (rect.y() + rect.height() > mMaxSelectionSize.height()) {
		rect.setHeight(mMaxSelectionSize.height() - rect.y());
	}

	return rect;
}

}
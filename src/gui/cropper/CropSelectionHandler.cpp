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
		mSelectionHandles.append(QRect(0, 0, Constants::ResizeHandleSize, Constants::ResizeHandleSize));
	}
}

QRect CropSelectionHandler::selection() const
{
	return mSelection;
}

QVector<QRect> CropSelectionHandler::selectionHandles() const
{
	return mSelectionHandles;
}

void CropSelectionHandler::grabHandle(const QPoint &position)
{
	for (auto handle : mSelectionHandles) {
		if (handle.contains(position)) {
			mGrabbedHandleIndex = mSelectionHandles.indexOf(handle);
			mGrabOffset = position - handle.center();
			break;
		}
	}
	mIsResizing = true;
	update();
}

void CropSelectionHandler::moveHandle(const QPoint &position)
{
	if (mGrabbedHandleIndex != -1) {
		auto newSelection = ShapeHelper::setRectPointAtIndex(mSelection, mGrabbedHandleIndex, position - mGrabOffset).toRect();
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
	mSelection = mAnnotationArea->sceneRect().toRect();
	mMaxSelectionSize = mAnnotationArea->sceneRect().toRect();
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
	mSelectionHandles[0].moveCenter(ShapeHelper::rectTopLeftWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[1].moveCenter(ShapeHelper::rectTop(mSelection).toPoint());
	mSelectionHandles[2].moveCenter(ShapeHelper::rectTopRightWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[3].moveCenter(ShapeHelper::rectRight(mSelection).toPoint());
	mSelectionHandles[4].moveCenter(ShapeHelper::rectBottomRightWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[5].moveCenter(ShapeHelper::rectBottom(mSelection).toPoint());
	mSelectionHandles[6].moveCenter(ShapeHelper::rectBottomLeftWithOffset(mSelection, 0).toPoint());
	mSelectionHandles[7].moveCenter(ShapeHelper::rectLeft(mSelection).toPoint());
}

QRect &CropSelectionHandler::trimToViewPort(QRect &rect) const
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
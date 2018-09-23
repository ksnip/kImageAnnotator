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
                                                                             mIsInMotion(false),
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

void CropSelectionHandler::grab(const QPointF &position)
{
	for (auto handle : mSelectionHandles) {
		if (handle.contains(position)) {
			mGrabbedHandleIndex = mSelectionHandles.indexOf(handle);
			mGrabOffset = position - ShapeHelper::rectPointAtIndex(mSelection, mGrabbedHandleIndex);
			mIsInMotion = true;
			update();
			break;
		}
	}

	if (mGrabbedHandleIndex == -1) {
		mSelection.contains(position);
		mGrabOffset = position - mSelection.topLeft();
		mIsInMotion = true;
		update();
	}
}

void CropSelectionHandler::move(const QPointF &position)
{
	if (mIsInMotion) {
		if (mGrabbedHandleIndex != -1) {
			auto newSelection = ShapeHelper::setRectPointAtIndex(mSelection, mGrabbedHandleIndex, position - mGrabOffset);
			setSelection(mSelectionRestrictor.restrictResize(newSelection, mSelection, mMaxSelection));
		} else {
			auto newSelection = mSelection;
			newSelection.moveTopLeft(position - mGrabOffset);
			setSelection(mSelectionRestrictor.restrictMove(newSelection, mMaxSelection));
		}
		update();
	}
}

void CropSelectionHandler::release()
{
	if (mIsInMotion) {
		mGrabbedHandleIndex = -1;
		mIsInMotion = false;
		update();
	}
}

void CropSelectionHandler::resetSelection()
{
	mMaxSelection = mAnnotationArea->sceneRect();
	setSelection(mAnnotationArea->sceneRect());
}

bool CropSelectionHandler::isInMotion() const
{
	return mIsInMotion;
}

void CropSelectionHandler::setWidth(int width)
{
	QRectF newSelection(mSelection.x(), mSelection.y(), width, mSelection.height());
	setSelection(mSelectionRestrictor.restrictResize(newSelection, mSelection, mMaxSelection));
}

void CropSelectionHandler::setHeight(int height)
{
	QRectF newSelection(mSelection.x(), mSelection.y(), mSelection.width(), height);
	setSelection(mSelectionRestrictor.restrictResize(newSelection, mSelection, mMaxSelection));
}

void CropSelectionHandler::setPositionX(int x)
{
	QRectF newSelection(x, mSelection.y(), mSelection.width(), mSelection.height());
	setSelection(mSelectionRestrictor.restrictMove(newSelection, mMaxSelection));
}

void CropSelectionHandler::setPositionY(int y)
{
	QRectF newSelection(mSelection.x(), y, mSelection.width(), mSelection.height());
	setSelection(mSelectionRestrictor.restrictMove(newSelection, mMaxSelection));
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

void CropSelectionHandler::setSelection(const QRectF &rect)
{
	mSelection = rect;
	update();
}

}
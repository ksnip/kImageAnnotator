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

CropSelectionHandler::CropSelectionHandler(AnnotationArea *annotationArea) : mAnnotationArea(annotationArea)
{
	resetSelection();
}

QRectF CropSelectionHandler::selection() const
{
	return mSelection;
}

QVector<QRectF> CropSelectionHandler::selectionHandles() const
{
	return mCropHandles.handles();
}

void CropSelectionHandler::grab(const QPointF &position)
{
	mCropHandles.grabHandle(position, mSelection);

	if (!mCropHandles.isHandleGrabbed()) {
		mMoveHelper.grabSelection(position, mSelection);
	}

	if (isInMotion()) {
		update();
	}
}

void CropSelectionHandler::move(const QPointF &position)
{
	if (mCropHandles.isHandleGrabbed()) {
		auto newSelection = ShapeHelper::setRectPointAtIndex(mSelection, mCropHandles.grabbedIndex(), position - mCropHandles.grabOffset());
		setSelection(mSelectionRestrictor.restrictResize(newSelection, mSelection, mMaxSelection));
	} else if (mMoveHelper.isSelectionGabbed()) {
		auto newSelection = mSelection;
		newSelection.moveTopLeft(position - mMoveHelper.grabOffset());
		setSelection(mSelectionRestrictor.restrictMove(newSelection, mMaxSelection));
	}

	if (isInMotion()) {
		update();
	}
}

void CropSelectionHandler::release()
{
	if (isInMotion()) {
		mCropHandles.releaseHandle();
		mMoveHelper.releaseSelection();
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
	return mMoveHelper.isSelectionGabbed() || mCropHandles.isHandleGrabbed();
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
	mCropHandles.updateHandles(mSelection);
	mAnnotationArea->update();
	notifyAboutChange();
}

void CropSelectionHandler::notifyAboutChange() const
{
	emit selectionChanged(mSelection);
}

void CropSelectionHandler::setSelection(const QRectF &rect)
{
	mSelection = rect;
	update();
}

bool CropSelectionHandler::selectionContains(const QPointF &pos) const
{
	return mSelection.contains(pos);
}

}
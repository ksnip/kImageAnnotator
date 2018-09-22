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

}

QRect CropSelectionHandler::selection() const
{
	return mSelection;
}

QList<QRect> CropSelectionHandler::selectionHandles() const
{
	return mSelectionHandles;
}

void CropSelectionHandler::grabHandle(const QPoint &position)
{

}

void CropSelectionHandler::moveHandle(const QPoint &position)
{

}

void CropSelectionHandler::resetSelection()
{
	mSelection = mAnnotationArea->sceneRect().toRect();
	mMaxSelectionSize = mAnnotationArea->sceneRect().toRect().size();
	notifyAboutChanged();
}

void CropSelectionHandler::setWidth(int width)
{
	if ((mSelection.x() + width) <= mMaxSelectionSize.width()) {
		mSelection.setWidth(width);
	} else {
		mSelection.setWidth(mMaxSelectionSize.width() - mSelection.x());
	}
	notifyAboutChanged();
}

void CropSelectionHandler::setHeight(int height)
{
	if ((mSelection.y() + height) <= mMaxSelectionSize.height()) {
		mSelection.setHeight(height);
	} else {
		mSelection.setHeight(mMaxSelectionSize.height() - mSelection.y());
	}
	notifyAboutChanged();
}

void CropSelectionHandler::setPositionX(int x)
{
	if ((x + mSelection.width()) <= mMaxSelectionSize.width()) {
		mSelection.moveTo(x, mSelection.y());
	} else {
		mSelection.moveTo(mMaxSelectionSize.width() - mSelection.width(), mSelection.y());
	}
	notifyAboutChanged();
}

void CropSelectionHandler::setPositionY(int y)
{
	if ((y + mSelection.height()) <= mMaxSelectionSize.height()) {
		mSelection.moveTo(mSelection.x(), y);
	} else {
		mSelection.moveTo(mSelection.x(), mMaxSelectionSize.height() - mSelection.height());
	}
	notifyAboutChanged();
}

void CropSelectionHandler::notifyAboutChanged() const
{
	mAnnotationArea->update();
	emit selectionChanged(mSelection);
}

}
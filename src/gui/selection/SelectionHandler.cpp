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

#include "SelectionHandler.h"

namespace kImageAnnotator {

SelectionHandler::SelectionHandler(ISelectionRestrictor *selectionRestrictor) :
	mAnnotationArea(nullptr),
	mSelectionRestrictor(selectionRestrictor),
	mRestrictionEnabled(true)
{

}

SelectionHandler::~SelectionHandler()
{
	delete mSelectionRestrictor;
}

void SelectionHandler::init(AnnotationArea *annotationArea)
{
	mAnnotationArea = annotationArea;
}

QRectF SelectionHandler::selection() const
{
	return mSelection;
}

QVector<QRectF> SelectionHandler::selectionHandles() const
{
	return mHandles.handles();
}

void SelectionHandler::grab(const QPointF &position)
{
	mHandles.grabHandle(position, mSelection);

	if (!mHandles.isHandleGrabbed()) {
		mMoveHelper.grabSelection(position, mSelection);
	}

	if (isInMotion()) {
		update();
	}
}

void SelectionHandler::move(const QPointF &position)
{
	if (mHandles.isHandleGrabbed()) {
		auto selection = ShapeHelper::setRectPointAtIndex(mSelection, mHandles.grabbedIndex(), position - mHandles.grabOffset());
		setSelection(restrictResize(selection));
	} else if (mMoveHelper.isSelectionGabbed()) {
		auto selection = mSelection;
		selection.moveTopLeft(position - mMoveHelper.grabOffset());
		setSelection(restrictMove(selection));
	}

	if (isInMotion()) {
		update();
	}
}

void SelectionHandler::release()
{
	if (isInMotion()) {
		mHandles.releaseHandle();
		mMoveHelper.releaseSelection();
		update();
	}
}

void SelectionHandler::resetSelection(const QRectF &selection, const QRectF &selectionLimit)
{
	Q_ASSERT(mAnnotationArea != nullptr);

	setSelection(selection);
	mSelectionLimit = selectionLimit;
}

bool SelectionHandler::isInMotion() const
{
	return mMoveHelper.isSelectionGabbed() || mHandles.isHandleGrabbed();
}

void SelectionHandler::setWidth(int width)
{
	QRectF selection(mSelection.x(), mSelection.y(), width, mSelection.height());
	setSelection(restrictResize(selection));
}

void SelectionHandler::setHeight(int height)
{
	QRectF selection(mSelection.x(), mSelection.y(), mSelection.width(), height);
	setSelection(restrictResize(selection));
}

void SelectionHandler::setPositionX(int x)
{
	QRectF selection(x, mSelection.y(), mSelection.width(), mSelection.height());
	setSelection(restrictMove(selection));
}

void SelectionHandler::setPositionY(int y)
{
	QRectF selection(mSelection.x(), y, mSelection.width(), mSelection.height());
	setSelection(restrictMove(selection));
}

void SelectionHandler::update()
{
	Q_ASSERT(mAnnotationArea != nullptr);

	mHandles.updateHandles(mSelection);
	mAnnotationArea->update();
	notifyAboutChange();
}

void SelectionHandler::notifyAboutChange() const
{
	emit selectionChanged(mSelection);
}

void SelectionHandler::setSelection(const QRectF &rect)
{
	mSelection = rect;
	update();
}

bool SelectionHandler::selectionContains(const QPointF &pos) const
{
	return mSelection.contains(pos);
}

void SelectionHandler::setRestrictionEnabled(bool enabled)
{
	mRestrictionEnabled = enabled;
	restrictResize(mSelection);
	update();
}

QRectF &SelectionHandler::restrictResize(QRectF &selection)
{
	if(mRestrictionEnabled) {
		return mSelectionRestrictor->restrictResize(selection, mSelection, mSelectionLimit) ;
	} else {
		return selection.isValid() ? selection : mSelection;
	}
}

QRectF &SelectionHandler::restrictMove(QRectF &selection) const
{
	return mRestrictionEnabled ? mSelectionRestrictor->restrictMove(selection, mSelectionLimit) : selection;
}

bool SelectionHandler::restrictionEnabled() const
{
	return mRestrictionEnabled;
}

}
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

#include "AnnotationItemModifier.h"

namespace kImageAnnotator {

AnnotationItemModifier::AnnotationItemModifier(ZoomValueProvider *zoomValueProvider)
{
	mItemSelector = new AnnotationItemSelector(zoomValueProvider);
	mItemResizer = new AnnotationMultiItemResizer(zoomValueProvider);
	mItemMover = new AnnotationItemMover();
	addToGroup(mItemSelector);
	addToGroup(mItemResizer);
	setZValue(1000);
	setAcceptHoverEvents(true);

	connect(mItemMover, &AnnotationItemMover::newCommand, this, &AnnotationItemModifier::itemChanged);
	connect(mItemResizer, &AnnotationMultiItemResizer::newCommand, this, &AnnotationItemModifier::itemChanged);
}

AnnotationItemModifier::~AnnotationItemModifier()
{
	delete mItemResizer;
	delete mItemSelector;
	delete mItemMover;
}

void AnnotationItemModifier::handleMousePress(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool isCtrlPressed)
{
	mItemResizer->grabHandle(pos);
	if (mItemResizer->isResizing()) {
		mItemResizer->hideCurrentResizer();
		return;
	}

	mItemSelector->handleSelectionOrShowSelectionRectAt(pos, items, isCtrlPressed);
	if (mItemSelector->isSelecting()) {
		mItemResizer->detach();
		return;
	}

	auto selectedItems = mItemSelector->selectedItems();
	mItemMover->setOffset(pos, selectedItems);
	mItemResizer->hide();

	handleSelection();
	updateCursor(mItemMover->cursor());
}

void AnnotationItemModifier::handleMouseMove(const QPointF &pos)
{
	if (mItemResizer->isResizing()) {
		mItemResizer->moveHandle(pos);
		updateCursor(mItemResizer->cursorForCurrentHandle());
	} else if (mItemSelector->isSelecting()) {
		mItemSelector->extendSelectionRectWhenShown(pos);
	} else {
		mItemMover->moveItems(pos);
		mItemSelector->refresh();
	}
}

void AnnotationItemModifier::handleMouseRelease(QList<AbstractAnnotationItem *> *items)
{
	if (mItemResizer->isResizing()) {
		mItemResizer->releaseHandle();
		mItemResizer->showCurrentResizer();
	} else if (mItemSelector->isSelecting()) {
		mItemSelector->finishSelectionRectWhenShown(items);
	} else {
		mItemMover->clearOffset();
		mItemResizer->show();
		updateCursor(mItemMover->cursor());
	}

	handleSelection();
}

void AnnotationItemModifier::handleSelectionAt(const QPointF &pos, QList<AbstractAnnotationItem *> *items, bool isCtrlPressed)
{
	mItemSelector->handleSelectionAt(pos, items, isCtrlPressed);
	handleSelection();
}

QList<AbstractAnnotationItem *> AnnotationItemModifier::selectedItems() const
{
	return mItemSelector->selectedItems();
}

QRectF AnnotationItemModifier::boundingRect() const
{
	if (mItemResizer->hasItemsAttached()) {
		return mItemResizer->boundingRect();
	}
	return mItemSelector->boundingRect();
}

void AnnotationItemModifier::clear()
{
	mItemSelector->clearSelection();
	mItemResizer->detach();
}

void AnnotationItemModifier::updateSelection()
{
	mItemSelector->update();
	mItemResizer->update();
	mItemResizer->refresh();
}

void AnnotationItemModifier::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	Q_UNUSED(event)
	// Move Cursor disappears when we let this event propagate
}

void AnnotationItemModifier::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	if (mItemMover->isMoving()) {
		return;
	}

	updateCursor(mItemResizer->cursorForPos(event->scenePos()));
	QGraphicsItemGroup::hoverMoveEvent(event);
}

void AnnotationItemModifier::handleSelection()
{
	auto selectedItems = mItemSelector->selectedItems();
	auto count = selectedItems.count();
	if (count == 0) {
		clear();
	} else {
        mItemResizer->attachTo(selectedItems);
	}
	emit itemsSelected(selectedItems);
}

void AnnotationItemModifier::updateCursor(Qt::CursorShape cursor)
{
	if (cursor == CursorHelper::defaultCursor()) {
		unsetCursor();
	} else {
		setCursor(cursor);
	}
}

void AnnotationItemModifier::itemChanged(QUndoCommand *command)
{
	emit itemModified();
	emit newCommand(command);
}

} // namespace kImageAnnotator

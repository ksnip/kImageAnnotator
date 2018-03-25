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

#include "AnnotationItemModifier.h"

AnnotationItemModifier::AnnotationItemModifier()
{
    mItemResizer = new AnnotationItemResizer();
    mItemSelector = new AnnotationItemSelector();
    mItemMover = new AnnotationItemMover();
    addToGroup(mItemResizer);
    addToGroup(mItemSelector);
}

AnnotationItemModifier::~AnnotationItemModifier()
{
    delete mItemResizer;
    delete mItemSelector;
    delete mItemMover;
}

void AnnotationItemModifier::handleMousePress(const QPointF& pos, QList<AbstractAnnotationItem*> *items)
{
    mItemResizer->grabHandle(pos);
    if(!mItemResizer->isResizing()) {
        mItemSelector->handleSelectionAt(pos, items);
        if(!mItemSelector->isSelecting()) {
            auto selectedItems = mItemSelector->selectedItems();
            mItemMover->setOffset(pos, selectedItems);

            if(selectedItems.count() == 1) {
                mItemResizer->attachTo(selectedItems.first());
            }
        }
    }
}

void AnnotationItemModifier::handleMouseMove(const QPointF& pos)
{
    if(mItemResizer->isResizing()) {
        mItemResizer->moveHandle(pos);
    } else if(mItemSelector->isSelecting()) {
        mItemSelector->extendSelectionRectWhenShown(pos);
    } else {
        mItemMover->moveItems(pos);
    }
}

void AnnotationItemModifier::handleMouseRelease(QList<AbstractAnnotationItem*> *items)
{
    if(mItemResizer->isResizing()) {
        mItemResizer->releaseHandle();
    } else if(mItemSelector->isSelecting()) {
        mItemSelector->finishSelectionRectWhenShown(items);
    } else {
        mItemMover->clearOffset();
    }

    auto selectedItems = mItemSelector->selectedItems();
    if(selectedItems.count() == 0) {
        clearSelection();
    }
}

void AnnotationItemModifier::clearSelection()
{
    mItemSelector->clearSelection();
    mItemResizer->detach();
}

QList<AbstractAnnotationItem *> AnnotationItemModifier::selectedItems() const
{
    return mItemSelector->selectedItems();
}

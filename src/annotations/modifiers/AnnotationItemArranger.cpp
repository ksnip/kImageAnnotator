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

#include "AnnotationItemArranger.h"

namespace kImageAnnotator {

AnnotationItemArranger::AnnotationItemArranger(const QList<AbstractAnnotationItem *> selectedItems, QList<AbstractAnnotationItem *> *items)
{
    mSelectedItems = selectedItems;
    mItems = items;
}

void AnnotationItemArranger::bringToFront()
{
    moveForward(true);
}

void AnnotationItemArranger::bringForward()
{
    moveForward(false);
}

void AnnotationItemArranger::sendBackward()
{
    moveBackward(false);
}

void AnnotationItemArranger::sendToBack()
{
    moveBackward(true);
}

void AnnotationItemArranger::moveForward(bool toFront)
{
    QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> itemToSwap;
    for (auto selected : mSelectedItems) {
        for (auto i = mItems->count() - 1; i >= 0; i--) {
            auto item = mItems->value(i);
            if (ItemHelper::zValueGreaterThen(item, selected) && !mSelectedItems.contains(item)) {
                itemToSwap.append(qMakePair(selected, item));
                if (!toFront) {
                    break;
                }
            }
        }
    }

    createAndEmitArrangeCommand(itemToSwap);
}

void AnnotationItemArranger::moveBackward(bool toBack)
{
    QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> itemToSwap;
    for (auto i = mSelectedItems.count() - 1; i >= 0; i--) {
        auto selected = mSelectedItems.value(i);
        for (auto item : *mItems) {
            if (item->zValue() < selected->zValue() && !mSelectedItems.contains(item)) {
                itemToSwap.append(qMakePair(selected, item));

                if (!toBack) {
                    break;
                }
            }
        }
    }

    createAndEmitArrangeCommand(itemToSwap);
}

void AnnotationItemArranger::createAndEmitArrangeCommand(const QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> &itemToSwap) const
{
    emit newCommand(new ArrangeCommand(itemToSwap, mItems));
}

} // namespace kImageAnnotator

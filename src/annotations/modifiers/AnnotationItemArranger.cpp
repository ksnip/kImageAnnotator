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

#include "AnnotationItemArranger.h"

AnnotationItemArranger::AnnotationItemArranger(const QList<AbstractAnnotationItem*> selectedItems, QList<AbstractAnnotationItem*>* items)
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
    for(auto selected : mSelectedItems) {
        for(auto i = mItems->count() - 1; i >= 0; i--) {
            auto item = mItems->value(i);
            if(zValueGreaterThen(item, selected) && !mSelectedItems.contains(item)) {
                swapZValues(selected, item);
                if(!toFront) {
                    break;
                }
            }
        }
    }
    sortItemsByZValue();
}

void AnnotationItemArranger::moveBackward(bool toBack)
{
    for(auto i = mSelectedItems.count() - 1; i >= 0; i--) {
        auto selected = mSelectedItems.value(i);
        for(auto item : *mItems) {
            if(!zValueGreaterThen(item, selected) && !mSelectedItems.contains(item)) {
                swapZValues(selected, item);
                if(!toBack) {
                    break;
                }
            }
        }
    }
    sortItemsByZValue();
}

void AnnotationItemArranger::swapZValues(AbstractAnnotationItem* item1, AbstractAnnotationItem* item2)
{
    auto tmpZValue = item1->zValue();
    item1->setZValue(item2->zValue());
    item2->setZValue(tmpZValue);
}

void AnnotationItemArranger::sortItemsByZValue()
{
    qSort(mItems->begin(), mItems->end(), zValueGreaterThen);
}

bool zValueGreaterThen(const AbstractAnnotationItem* item1, const AbstractAnnotationItem* item2)
{
    return item1->zValue() > item2->zValue();
}

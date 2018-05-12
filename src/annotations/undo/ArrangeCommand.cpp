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

#include "ArrangeCommand.h"

ArrangeCommand::ArrangeCommand(QList<QPair<AbstractAnnotationItem *, AbstractAnnotationItem *>> itemToSwap, QList<AbstractAnnotationItem *> *allItems)
{
    mItemToSwap = itemToSwap;
    mAllItems = allItems;
}

void ArrangeCommand::undo()
{
    for (auto i = mItemToSwap.count() - 1; i >= 0; i--) {
        auto pair = mItemToSwap[i];
        swapZValues(pair.first, pair.second);
    }
    sortItemsByZValue();
}

void ArrangeCommand::redo()
{
    for (auto pair : mItemToSwap) {
        swapZValues(pair.first, pair.second);
    }
    sortItemsByZValue();
}

void ArrangeCommand::swapZValues(AbstractAnnotationItem *item1, AbstractAnnotationItem *item2) const
{
    auto tmpZValue = item1->zValue();
    item1->setZValue(item2->zValue());
    item2->setZValue(tmpZValue);
}

void ArrangeCommand::sortItemsByZValue()
{
    qSort(mAllItems->begin(), mAllItems->end(), ItemHelper::zValueGreaterThen);
}

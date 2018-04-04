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

#include "AnnotationItemSelector.h"

AnnotationItemSelector::AnnotationItemSelector()
{
    mSelectedItems = new QList<AbstractAnnotationItem*>();
    mShowSelectionRect = false;
}

AnnotationItemSelector::~AnnotationItemSelector()
{
    delete mSelectedItems;
}

QRectF AnnotationItemSelector::boundingRect() const
{
    if(isSelecting()) {
        return mSelectionRect.normalized();
    } else {
        return mSelectedItemsBoundingRect;
    }
}

void AnnotationItemSelector::handleSelectionAt(const QPointF& pos, QList<AbstractAnnotationItem*>* items)
{
    selectItemAtPosition(pos, items);
    if(mSelectedItems->count() > 0) {
        return;
    }

    prepareGeometryChange();
    initSelectionRectAt(pos);
    mShowSelectionRect = true;
}

void AnnotationItemSelector::extendSelectionRectWhenShown(const QPointF& pos)
{
    if(!mShowSelectionRect) {
        return;
    }

    prepareGeometryChange();
    updateSelectionRect(pos);
}

void AnnotationItemSelector::finishSelectionRectWhenShown(QList<AbstractAnnotationItem*>* items)
{
    if(!mShowSelectionRect) {
        return;
    }

    prepareGeometryChange();
    selectItemsUnderRect(items);
    mShowSelectionRect = false;
}

void AnnotationItemSelector::clearSelection()
{
    prepareGeometryChange();
    mSelectedItems->clear();
    mSelectedItemsBoundingRect = QRectF();
}

QList<AbstractAnnotationItem*> AnnotationItemSelector::selectedItems() const
{
    return *mSelectedItems;
}

bool AnnotationItemSelector::isSelecting() const
{
    return mShowSelectionRect;
}

void AnnotationItemSelector::refresh()
{
    prepareGeometryChange();
    mSelectedItemsBoundingRect = QRectF();
    for(auto item : *mSelectedItems) {
        addItemToBoundingRect(item);
    }
}

void AnnotationItemSelector::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(mShowSelectionRect) {
        painter->setPen(Qt::darkBlue);
        painter->setBrush(QColor(0, 0, 255, 60));
        painter->drawRect(mSelectionRect);
    }

    painter->setPen(Qt::gray);
    painter->setBrush(Qt::NoBrush);
    for(auto item : *mSelectedItems) {
        painter->drawRect(item->boundingRect());
    }
}

void AnnotationItemSelector::initSelectionRectAt(const QPointF& position)
{
    mSelectionRect.setTopLeft(position);
    updateSelectionRect(position);
}

void AnnotationItemSelector::updateSelectionRect(const QPointF& position)
{
    mSelectionRect.setBottomRight(position);
}

void AnnotationItemSelector::selectItemAtPosition(const QPointF& position, QList<AbstractAnnotationItem*>* items)
{
    QRectF rect(position - QPointF(2, 2), QSize(4, 4));

    for(auto item : *items) {
        if(item->intersects(rect)) {
            if(!mSelectedItems->contains(item)) {
                clearSelection();
                selectItem(item);
            }
            return;
        }
    }
    clearSelection();
}

void AnnotationItemSelector::selectItemsUnderRect(QList<AbstractAnnotationItem*>* items)
{
    clearSelection();
    for(auto item : *items) {
        if(item->intersects(mSelectionRect)) {
            selectItem(item);
        }
    }
}

void AnnotationItemSelector::selectItem(AbstractAnnotationItem* item)
{
    mSelectedItems->append(item);
    addItemToBoundingRect(item);
}

void AnnotationItemSelector::addItemToBoundingRect(AbstractAnnotationItem* item)
{
    mSelectedItemsBoundingRect = mSelectedItemsBoundingRect.united(item->boundingRect());
}

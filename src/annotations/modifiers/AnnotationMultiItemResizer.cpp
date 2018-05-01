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

#include "AnnotationMultiItemResizer.h"

AnnotationMultiItemResizer::AnnotationMultiItemResizer()
{
    mCurrentResizer = nullptr;
}

QRectF AnnotationMultiItemResizer::boundingRect() const
{
    QRectF rect;
    for (auto resizer : childItems()) {
        rect = rect.united(resizer->boundingRect());
    }
    return rect;
}

void AnnotationMultiItemResizer::attachTo(QList<AbstractAnnotationItem*> items)
{
    detach();
    for(auto item : items) {
        auto resizer = getResizerForItem(item);
        showResizer(resizer);
    }
}

void AnnotationMultiItemResizer::detach()
{
    for(auto resizer : childItems()) {
        hideResizer(resizer);
    }

    mCurrentResizer = nullptr;
}

void AnnotationMultiItemResizer::grabHandle(const QPointF &pos)
{
    for(auto item : childItems()) {
        auto resizer = castToResizer(item);
        resizer->grabHandle(pos);
        if(resizer->isResizing()) {
            mCurrentResizer = resizer;
            return;
        }
    }
    mCurrentResizer = nullptr;
}

void AnnotationMultiItemResizer::moveHandle(const QPointF &pos)
{
    if(mCurrentResizer == nullptr) {
        return;
    }

    mCurrentResizer->moveHandle(pos);
}

void AnnotationMultiItemResizer::releaseHandle()
{
    if(mCurrentResizer == nullptr) {
        return;
    }

    mCurrentResizer->releaseHandle();
}

bool AnnotationMultiItemResizer::isResizing() const
{
    return mCurrentResizer != nullptr && mCurrentResizer->isResizing();
}

void AnnotationMultiItemResizer::refresh()
{
    for(auto item : childItems()) {
        auto resizer = castToResizer(item);
        resizer->refresh();
    }
}

void AnnotationMultiItemResizer::update()
{
    for(auto item : childItems()) {
        auto resizer = castToResizer(item);
        if(!resizer->isItemVisible()) {
            hideResizer(resizer);
        }
    }
}

bool AnnotationMultiItemResizer::hasItemsAttached() const
{
    return childItems().count() > 0;
}

Qt::CursorShape AnnotationMultiItemResizer::cursorForPos(const QPointF &pos)
{
    for(auto item : childItems()) {
        auto resizer = castToResizer(item);
        if(resizer->boundingRect().contains(pos)) {
            return resizer->cursorForPos(pos);
        }
    }

    return CursorHelper::defaultCursor();
}

Qt::CursorShape AnnotationMultiItemResizer::cursorForCurrentHandle()
{
    if(mCurrentResizer == nullptr) {
        return CursorHelper::defaultCursor();
    }
    return mCurrentResizer->cursorForCurrentHandle();
}

AnnotationItemResizer* AnnotationMultiItemResizer::getResizerForItem(AbstractAnnotationItem *item)
{
    if(!mItemToResizer.contains(item)) {
        mItemToResizer[item] = new AnnotationItemResizer(item);
    }

    return mItemToResizer[item];
}

void AnnotationMultiItemResizer::hideResizer(QGraphicsItem *resizer)
{
    removeFromGroup(resizer);
    resizer->hide();
}

void AnnotationMultiItemResizer::showResizer(AnnotationItemResizer *resizer)
{
    addToGroup(resizer);
    resizer->show();
}

AnnotationItemResizer *AnnotationMultiItemResizer::castToResizer(QGraphicsItem *item) const
{
    return dynamic_cast<AnnotationItemResizer*>(item);
}

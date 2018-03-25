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

#include "AnnotationArea.h"

AnnotationArea::AnnotationArea()
{
    mConfig = Config::instance();
    mItemFactory = new AnnotationItemFactory();
    mBackgroundImage = nullptr;
    mCurrentItem = nullptr;
    mItems = new QList<AbstractAnnotationItem*>();
    mItemModifier = new AnnotationItemModifier();
    addItem(mItemModifier);
}

AnnotationArea::~AnnotationArea()
{
    delete mItemFactory;
    delete mItems;
    delete mItemModifier;
}

void AnnotationArea::setBackgroundImage(const QPixmap& image)
{
    if(image.isNull()) {
        return;
    }

    mBackgroundImage = addPixmap(image);
}

QImage AnnotationArea::exportAsImage()
{
    if(mBackgroundImage == nullptr) {
        return QImage();
    }

    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render(&painter);
    return image;
}

void AnnotationArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        if(mConfig->selectedTool() == ToolTypes::Select) {
            mItemModifier->handleMousePress(event->scenePos(), mItems);
        } else {
            clearSelection();
            addItemAtPosition(event->scenePos());
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void AnnotationArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->buttons() == Qt::LeftButton) {
        if(mCurrentItem) {
            addPointToCurrentItem(event->scenePos());
        } else {
            mItemModifier->handleMouseMove(event->scenePos());
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void AnnotationArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        if(mConfig->selectedTool() == ToolTypes::Select) {
            mItemModifier->handleMouseRelease(mItems);
        } else {
            mCurrentItem = nullptr;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void AnnotationArea::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key()) {
        case Qt::Key_Delete:
            deleteSelectedItems();
            break;
        case Qt::Key_Escape:
            mItemModifier->clearSelection();
            break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void AnnotationArea::addItemAtPosition(const QPointF& position)
{
    mCurrentItem = mItemFactory->createItem(position, mConfig->selectedTool());

    mItems->prepend(mCurrentItem);
    addItem(mCurrentItem);
}

void AnnotationArea::addPointToCurrentItem(const QPointF& position)
{
    mCurrentItem->addPoint(position);
}

void AnnotationArea::deleteSelectedItems()
{
    auto selectedItems = mItemModifier->selectedItems();
    mItemModifier->clearSelection();

    for(auto item : selectedItems) {
        removeItem(item);
        mItems->removeOne(item);
        delete item;
    }
}

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

AnnotationArea::AnnotationArea(AnnotationItemFactory *itemFactory)
{
    mItemFactory = itemFactory;
    mBackgroundImage = nullptr;
    mCurrentItem = nullptr;
    mItemModifier = new AnnotationItemModifier();
    mItemModifier->setZValue(100);
    addItem(mItemModifier);
}

AnnotationArea::~AnnotationArea()
{
    delete mItemFactory;
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

void AnnotationArea::setToolType(AnnotationToolTypes toolType)
{
    mSelectedToolType = toolType;
}

void AnnotationArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        if(mSelectedToolType == AnnotationToolTypes::Select) {
            mCurrentItem = findItemAt(event->scenePos());
            if(mCurrentItem != nullptr) {
                mItemModifier->attachTo((AbstractAnnotationLine*)mCurrentItem);
            }
        } else {
            addItemAtPosition(event->scenePos());
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void AnnotationArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->buttons() == Qt::LeftButton) {
        if(mSelectedToolType == AnnotationToolTypes::Select) {

        } else {
            addPointToCurrentItem(event->scenePos());
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void AnnotationArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        if(mSelectedToolType == AnnotationToolTypes::Select) {

        } else {
            mCurrentItem = nullptr;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void AnnotationArea::addItemAtPosition(const QPointF& position)
{
    mCurrentItem = mItemFactory->createItem(position);
    addItem(mCurrentItem);
}

void AnnotationArea::addPointToCurrentItem(const QPointF& position)
{
    mCurrentItem->addPoint(position);
}

AbstractAnnotationItem* AnnotationArea::findItemAt(const QPointF& point) const
{
    QRectF rect(point - QPointF(2, 2), QSize(4, 4));

    for(auto item : items()) {
        auto baseItem = dynamic_cast<AbstractAnnotationItem*> (item);

        if(baseItem != nullptr && baseItem->intersects(rect)) {
            return baseItem;
        }
    }
    return nullptr;
}

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

AnntationArea::AnntationArea(AnnotationItemFactory *itemFactory)
{
    mItemFactory = itemFactory;
    mBackgroundImage = nullptr;
}

AnntationArea::~AnntationArea()
{
    delete mItemFactory;
}

void AnntationArea::setBackgroundImage(const QPixmap& image)
{
    if(image.isNull()) {
        return;
    }

    mBackgroundImage = addPixmap(image);

    //REMOVE
    auto item = mItemFactory->createItem(QPointF(20, 20));
    item->addPoint(QPointF(300, 300));
    addItem(item);
}

QImage AnntationArea::exportAsImage()
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

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

#include "CropCommand.h"

namespace kImageAnnotator {

CropCommand::CropCommand(QGraphicsPixmapItem *image, const QRectF &cropRect, AnnotationArea *annotationArea)
{
	mAnnotationArea = annotationArea;
	mImageItem = image;
	mOriginalImage = QPixmap(image->pixmap());    
    QRect rect = ScaledSizeProvider::getScaledRect(cropRect.toRect(), image->pixmap().devicePixelRatio());
    mCroppedImage = QPixmap(image->pixmap().copy(rect));
    mNewItemOffset = rect.topLeft();
}

void CropCommand::undo()
{
	for (auto item : mAnnotationArea->items()) {
		auto baseItem = dynamic_cast<AbstractAnnotationItem *>(item);
		if (baseItem != nullptr) {
			baseItem->setPosition(baseItem->position() + mNewItemOffset);
		}
	}

	mImageItem->setPixmap(mOriginalImage);
	mAnnotationArea->setSceneRect(mImageItem->boundingRect());
}

void CropCommand::redo()
{
	for (auto item : mAnnotationArea->items()) {
		auto baseItem = dynamic_cast<AbstractAnnotationItem *>(item);
		if (baseItem != nullptr) {
			baseItem->setPosition(baseItem->position() - mNewItemOffset);
		}
	}

	mImageItem->setPixmap(mCroppedImage);
	mAnnotationArea->setSceneRect(mImageItem->boundingRect());
}

}

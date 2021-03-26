/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "RotateCommand.h"

namespace kImageAnnotator {

RotateCommand::RotateCommand(QGraphicsPixmapItem *backgroundImage, qreal angel, AnnotationArea *annotationArea) :
	mBackgroundImage(backgroundImage),
	mAnnotationArea(annotationArea),
	mOldPixmap(mBackgroundImage->pixmap())
{
	mNewPixmap = rotatePixmap(mOldPixmap, angel);
}

void RotateCommand::undo()
{
	mBackgroundImage->setPixmap(mOldPixmap);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

void RotateCommand::redo()
{
	mBackgroundImage->setPixmap(mNewPixmap);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

QPixmap RotateCommand::rotatePixmap(const QPixmap &sourcePixmap, qreal angel)
{
	auto center = sourcePixmap.rect().center();
	QTransform transform;
	transform.translate(center.x(), center.y());
	transform.rotate(angel);
	transform.translate(-center.x(), -center.y());
	auto rotatedPixmap = sourcePixmap.transformed(transform, Qt::SmoothTransformation);
	auto nonTransparentContentRect = QRegion(rotatedPixmap.mask()).boundingRect();
	return rotatedPixmap.copy(nonTransparentContentRect);
}

} // namespace kImageAnnotator
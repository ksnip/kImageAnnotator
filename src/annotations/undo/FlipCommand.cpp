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

#include "FlipCommand.h"

namespace kImageAnnotator {

FlipCommand::FlipCommand(QGraphicsPixmapItem *backgroundImage, FlipDirection direction, AnnotationArea *annotationArea) :
	mBackgroundImage(backgroundImage),
	mAnnotationArea(annotationArea),
	mOldPixmap(backgroundImage->pixmap())
{
	mNewPixmap = flipPixmap(mOldPixmap, direction);
}

void FlipCommand::undo()
{
	mBackgroundImage->setPixmap(mOldPixmap);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

void FlipCommand::redo()
{
	mBackgroundImage->setPixmap(mNewPixmap);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

QPixmap FlipCommand::flipPixmap(const QPixmap &sourcePixmap, FlipDirection direction)
{
	auto flipHorizontal = direction == FlipDirection::Horizontal;
	auto flipVertical = direction == FlipDirection::Vertical;
	auto flippedImage = sourcePixmap.toImage().mirrored(flipHorizontal, flipVertical);
	return QPixmap::fromImage(flippedImage);
}

} // namespace kImageAnnotator
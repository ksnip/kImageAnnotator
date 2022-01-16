/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#include "CutCommand.h"

namespace kImageAnnotator {

CutCommand::CutCommand(QGraphicsPixmapItem *backgroundImage, const QRectF &cutOutRect, AnnotationArea *annotationArea) :
	mAnnotationArea(annotationArea),
	mBackgroundImage(backgroundImage),
	mOriginalImage(backgroundImage->pixmap())
{
	auto imageRect = backgroundImage->boundingRect();
	if(isVerticalCut(cutOutRect, imageRect)) {
		createCutImage(imageRect, cutOutRect.bottomLeft(), cutOutRect.topRight(), cutOutRect.topLeft());
	} else {
		createCutImage(imageRect, cutOutRect.topRight(), cutOutRect.bottomLeft(), cutOutRect.topLeft());
	}
}

void CutCommand::undo()
{
	mBackgroundImage->setPixmap(mOriginalImage);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

void CutCommand::redo()
{
	mBackgroundImage->setPixmap(mCutImage);
	mAnnotationArea->setSceneRect(mBackgroundImage->boundingRect());
}

bool CutCommand::isVerticalCut(const QRectF &cutOutRect, const QRectF &imageRect) const
{
	return imageRect.top() == cutOutRect.top() && imageRect.bottom() == cutOutRect.bottom();
}

void CutCommand::createCutImage(const QRectF &imageRect, const QPointF &bottomRightRect1, const QPointF &topLeftRect2, const QPointF &connectionPoint)
{
	auto rect1 = QRectF(imageRect.topLeft(), bottomRightRect1);
	auto rect2 = QRectF(topLeftRect2, imageRect.bottomRight());
	auto image1 = mOriginalImage.copy(rect1.toRect());
	auto image2 = mOriginalImage.copy(rect2.toRect());

	rect2.moveTopLeft(connectionPoint);

	mCutImage = QPixmap(rect1.united(rect2).size().toSize());
	QPainter painter(&mCutImage);
	painter.drawPixmap(rect1.topLeft(), image1);
	painter.drawPixmap(rect2.topLeft(), image2);
}

} // namespace kImageAnnotator

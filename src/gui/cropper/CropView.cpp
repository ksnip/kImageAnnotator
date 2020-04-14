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

#include "CropView.h"

namespace kImageAnnotator {

CropView::CropView(CropSelectionHandler *cropSelectionHandler, KeyHelper *keyHelper) :
    mKeyHelper(keyHelper),
    mCropSelectionHandler(cropSelectionHandler)
{
}

void CropView::init(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	setScene(annotationArea);
}

void CropView::keyPressEvent(QKeyEvent *event)
{
	mKeyHelper->keyPress(event);
}

void CropView::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper->keyRelease(event);
}

void CropView::mouseMoveEvent(QMouseEvent *event)
{
	auto pos = mapToScene(event->pos());
	mCropSelectionHandler->move(pos);
	updateCursor(pos);
}

void CropView::mousePressEvent(QMouseEvent *event)
{
	auto pos = mapToScene(event->pos());
	mCropSelectionHandler->grab(pos);
	updateCursor(pos);
}

void CropView::mouseReleaseEvent(QMouseEvent *event)
{
	mCropSelectionHandler->release();
	updateCursor(mapToScene(event->pos()));
}

void CropView::drawForeground(QPainter *painter, const QRectF &rect)
{
	auto selection = mCropSelectionHandler->selection();

	// Draw semi transparent background for not selected area
	painter->setClipRegion(QRegion(sceneRect().toRect()).subtracted(QRegion(selection.toRect())));
	painter->setBrush(QColor(0, 0, 0, 150));
	painter->drawRect(sceneRect());


	// Draw border around selected are
	painter->setClipRect(rect);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	painter->drawRect(selection);

	if (!mCropSelectionHandler->isInMotion()) {
		painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
		painter->setBrush(QColor(Qt::gray));
		auto handles = mCropSelectionHandler->selectionHandles();

		for (auto handle : handles) {
			painter->drawRect(handle);
		}
	}

	QGraphicsView::drawForeground(painter, rect);
}

void CropView::updateCursor(const QPointF &pos)
{
	if(mCropSelectionHandler->isInMotion()) {
		setCursor(Qt::ClosedHandCursor);
	} else if(mCropSelectionHandler->selectionContains(pos)) {
		setCursor(Qt::OpenHandCursor);
	} else {
		unsetCursor();
	}
}

} // namespace kImageAnnotator

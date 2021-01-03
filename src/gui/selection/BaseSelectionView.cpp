/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "BaseSelectionView.h"

namespace kImageAnnotator {

BaseSelectionView::BaseSelectionView(SelectionHandler *cropSelectionHandler, KeyHelper *keyHelper) :
	mKeyHelper(keyHelper),
	mSelectionHandler(cropSelectionHandler)
{
}

void BaseSelectionView::init(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	setScene(annotationArea);
}

void BaseSelectionView::keyPressEvent(QKeyEvent *event)
{
	mKeyHelper->keyPress(event);
}

void BaseSelectionView::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper->keyRelease(event);
}

void BaseSelectionView::mouseMoveEvent(QMouseEvent *event)
{
	auto pos = mapToScene(event->pos());
	mSelectionHandler->move(pos);
	updateCursor(pos);
}

void BaseSelectionView::mousePressEvent(QMouseEvent *event)
{
	auto pos = mapToScene(event->pos());
	mSelectionHandler->grab(pos);
	updateCursor(pos);
}

void BaseSelectionView::mouseReleaseEvent(QMouseEvent *event)
{
	mSelectionHandler->release();
	updateCursor(mapToScene(event->pos()));
}

void BaseSelectionView::drawForeground(QPainter *painter, const QRectF &rect)
{
	auto selection = mSelectionHandler->selection();

	// Draw border around selected are
	painter->setClipRect(rect);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	painter->drawRect(selection);

	if (!mSelectionHandler->isInMotion()) {
		painter->setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
		painter->setBrush(QColor(Qt::gray));
		auto handles = mSelectionHandler->selectionHandles();

		for (auto handle : handles) {
			painter->drawRect(handle);
		}
	}

	QGraphicsView::drawForeground(painter, rect);
}

QRectF BaseSelectionView::currentSelection() const
{
	return mSelectionHandler->selection();
}

void BaseSelectionView::updateCursor(const QPointF &pos)
{
	if(mSelectionHandler->isInMotion()) {
		setCursor(Qt::ClosedHandCursor);
	} else if(mSelectionHandler->selectionContains(pos)) {
		setCursor(Qt::OpenHandCursor);
	} else {
		unsetCursor();
	}
}

} // namespace kImageAnnotator

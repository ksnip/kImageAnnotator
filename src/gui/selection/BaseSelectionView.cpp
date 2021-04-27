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

BaseSelectionView::BaseSelectionView(SelectionHandler *cropSelectionHandler, KeyHelper *keyHelper, QWidget *parent) :
	ScrollAndZoomView(parent),
	mKeyHelper(keyHelper),
	mSelectionHandler(cropSelectionHandler)
{
	connect(zoomValueProvider(), &ZoomValueProvider::zoomValueChanged, this, &BaseSelectionView::applyZoomValue);
}

void BaseSelectionView::init(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	setScene(annotationArea);
}

void BaseSelectionView::keyPressEvent(QKeyEvent *event)
{
	mKeyHelper->keyPress(event);
	ScrollAndZoomView::keyPressEvent(event);
}

void BaseSelectionView::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper->keyRelease(event);
	ScrollAndZoomView::keyReleaseEvent(event);
}

void BaseSelectionView::mouseMoveEvent(QMouseEvent *event)
{

	if (mSelectionHandler->isInMotion()) {
		mSelectionHandler->move(mapToScene(event->pos()));
	} else {
		ScrollAndZoomView::mouseMoveEvent(event);
	}
	updateCursor(mapToScene(event->pos()));
}

void BaseSelectionView::mousePressEvent(QMouseEvent *event)
{

	if(event->button() == Qt::LeftButton) {
		mSelectionHandler->grab(mapToScene(event->pos()));
	} else {
		ScrollAndZoomView::mousePressEvent(event);
	}
	updateCursor(mapToScene(event->pos()));
}

void BaseSelectionView::mouseReleaseEvent(QMouseEvent *event)
{
	if (mSelectionHandler->isInMotion()) {
		mSelectionHandler->release();
	} else {
		ScrollAndZoomView::mouseReleaseEvent(event);
	}
	updateCursor(mapToScene(event->pos()));
}

void BaseSelectionView::drawForeground(QPainter *painter, const QRectF &rect)
{
	auto selection = mSelectionHandler->selection();
	auto zoomValue = zoomValueProvider()->zoomValue();
	auto lineWidth = 1 / zoomValue;

	// Draw border around selected are
	painter->setClipRect(rect);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::gray, lineWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	painter->drawRect(selection);

	if (!mSelectionHandler->isInMotion()) {
		painter->setPen(QPen(Qt::white, lineWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
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

void BaseSelectionView::applyZoomValue(double value)
{
	mSelectionHandler->applyZoomValue(value);
}

} // namespace kImageAnnotator

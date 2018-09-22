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

CropView::CropView(kImageAnnotator::AnnotationArea *annotationArea, KeyHelper *keyHelper) : mKeyHelper(keyHelper)
{
	setScene(annotationArea);
	resetSelection();
}

QRect CropView::selection() const
{
	return mSelection;
}

void CropView::setSelection(const QRect &rect)
{
	mSelection = rect;
	notifyAboutChanged();
}

void CropView::resetSelection()
{
	mSelection = sceneRect().toRect();
	notifyAboutChanged();
}

QSize CropView::maxSelectionSize() const
{
	return sceneRect().size().toSize();
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
	notifyAboutChanged();
}

void CropView::mousePressEvent(QMouseEvent *event)
{

}

void CropView::mouseReleaseEvent(QMouseEvent *event)
{

}

void CropView::drawForeground(QPainter *painter, const QRectF &rect)
{
	// Draw semi transparent background for not selected area
	painter->setClipRegion(QRegion(sceneRect().toRect()).subtracted(
		QRegion(mSelection.normalized()))
	);
	painter->setBrush(QColor(0, 0, 0, 150));
	painter->drawRect(sceneRect());


	// Draw border around selected are
	painter->setClipRect(rect);
	painter->setBrush(Qt::NoBrush);
	painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
	painter->drawRect(mSelection.normalized());

	QGraphicsView::drawForeground(painter, rect);
}

void CropView::notifyAboutChanged() const
{
	scene()->update();
	emit selectionChanged(mSelection);
}

} // namespace kImageAnnotator

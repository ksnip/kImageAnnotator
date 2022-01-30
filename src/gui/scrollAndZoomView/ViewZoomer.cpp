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

#include "ViewZoomer.h"

namespace kImageAnnotator {

ViewZoomer::ViewZoomer(QGraphicsView *view) :
	ZoomValueProvider(view),
	mView(view),
	mMinScale(0.1),
	mMaxScale(8.0)
{

}

double ViewZoomer::zoomValue() const
{
	return mView->transform().m11();
}

void ViewZoomer::zoom(double factor)
{
	auto currentZoomValue = zoomValue();
	auto newZoomValue = currentZoomValue + factor;
	newZoomValue = QString::number(newZoomValue, 'f', 1).toDouble();

	if(newZoomValue >= mMinScale && newZoomValue <= mMaxScale) {
		mView->resetMatrix();
		mView->scale(newZoomValue, newZoomValue);
		emit zoomValueChanged(zoomValue());
	}
}

void ViewZoomer::zoomToPoint(double factor, const QPoint &viewPoint)
{
	const auto scenePoint = mView->mapToScene(viewPoint);
	zoom(factor);
	const auto delta = mView->mapToScene(viewPoint) - scenePoint;
	mView->translate(delta.x(), delta.y());
}

void ViewZoomer::wheelZoom(QWheelEvent *event)
{
	auto zoomInFactor = 0.1;

	const auto factor = event->angleDelta().y() < 0.0 ? -zoomInFactor : zoomInFactor;
	zoomToPoint(factor, event->pos());
	event->accept(); // supress scrolling
}

void ViewZoomer::fitImage()
{
	mView->fitInView(mView->sceneRect(), Qt::KeepAspectRatio);
}

void ViewZoomer::setZoomValue(double value)
{
	// ZoomPicker's mFitImageButton() sets value to -1
	if (value < 0) {
		fitImage();
		emit zoomValueChanged(zoomValue());
		return;
	}
	zoom(value - zoomValue());
}

} // namespace kImageAnnotator

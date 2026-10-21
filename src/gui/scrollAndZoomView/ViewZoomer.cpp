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

/*
 * Steps to the next multiple of the factor, for example from 0.75 to 0.8 or 0.7
 * with a factor of 0.1 or -0.1, so the zoom stays on clean values.
 */
void ViewZoomer::zoom(double factor)
{
	auto stepInPercent = qRound(qAbs(factor) * 100);
	if (stepInPercent == 0) {
		return;
	}

	auto currentInPercent = qRound(zoomValue() * 100);
	auto snappedInPercent = factor > 0
		? (currentInPercent / stepInPercent) * stepInPercent + stepInPercent
		: ((currentInPercent + stepInPercent - 1) / stepInPercent) * stepInPercent - stepInPercent;

	applyZoomValue(snappedInPercent / 100.0);
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
	zoomToPoint(factor, event->position().toPoint());
	event->accept(); // supress scrolling
}

void ViewZoomer::fitImageToView()
{
	mView->fitInView(mView->sceneRect(), Qt::KeepAspectRatio);
	emit zoomValueChanged(zoomValue());
}

/*
 * Sets the zoom to the given value, rounded to whole percent like the zoom
 * picker shows it.
 */
void ViewZoomer::setZoomValue(double value)
{
	applyZoomValue(qRound(value * 100) / 100.0);
}

void ViewZoomer::applyZoomValue(double value)
{
	if(value >= mMinScale && value <= mMaxScale) {
		mView->resetTransform();
		mView->scale(value, value);
		emit zoomValueChanged(zoomValue());
	}
}

} // namespace kImageAnnotator

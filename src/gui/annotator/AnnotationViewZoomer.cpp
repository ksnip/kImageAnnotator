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

#include "AnnotationViewZoomer.h"

namespace kImageAnnotator {

AnnotationViewZoomer::AnnotationViewZoomer(QGraphicsView *view) : ZoomValueProvider(view), mView(view)
{}

double AnnotationViewZoomer::zoomValue() const
{
	return mView->transform().m11();
}

void AnnotationViewZoomer::zoom(double factor)
{
	const auto minScale = 1.0;
	const auto maxScale = 8.0;
	const auto scaleFactor = qBound(minScale, factor * zoomValue(), maxScale) / zoomValue();
	if (!qFuzzyCompare(scaleFactor, 1.0)) {
		mView->scale(scaleFactor, scaleFactor);
		emit zoomValueChanged(zoomValue());
	}
}

void AnnotationViewZoomer::zoomToPoint(double factor, const QPoint &viewPoint)
{
	const auto scenePoint = mView->mapToScene(viewPoint);
	zoom(factor);
	const auto delta = mView->mapToScene(viewPoint) - scenePoint;
	mView->translate(delta.x(), delta.y());
}

void AnnotationViewZoomer::wheelZoom(QWheelEvent *event)
{
	const auto zoomInFactor = 1.1;
	const auto zoomOutFactor = 1.0 / zoomInFactor;
	const auto factor = (event->angleDelta().y() < 0.0) ? zoomOutFactor : zoomInFactor;
	zoomToPoint(factor, event->pos());
	event->accept(); // supress scrolling
}

} // namespace kImageAnnotator

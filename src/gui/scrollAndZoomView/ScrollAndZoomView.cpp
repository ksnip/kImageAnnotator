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

#include "ScrollAndZoomView.h"

namespace kImageAnnotator {

ScrollAndZoomView::ScrollAndZoomView(QWidget *parent) :
	QGraphicsView(parent),
	mIsDragging(false),
	mViewZoomer(new ViewZoomer(this))
{
	setTransformationAnchor(QGraphicsView::NoAnchor);
	disableDragging();
	setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);
}

ScrollAndZoomView::~ScrollAndZoomView()
{
	delete mViewZoomer;
}

ZoomValueProvider *ScrollAndZoomView::zoomValueProvider() const
{
	return mViewZoomer;
}

void ScrollAndZoomView::keyPressEvent(QKeyEvent *event)
{
	mKeyHelper.keyPress(event);
	if(mKeyHelper.isSpacePressed()) {
		enableDragging(mapFromGlobal(QCursor::pos()));
	}
	QGraphicsView::keyPressEvent(event);
}

void ScrollAndZoomView::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper.keyRelease(event);
	if(!mKeyHelper.isSpacePressed()) {
		disableDragging();
	}
	QGraphicsView::keyReleaseEvent(event);
}

void ScrollAndZoomView::mouseMoveEvent(QMouseEvent *event)
{
	if (mIsDragging) {
		scrollTo(event->pos());
	} else {
		QGraphicsView::mouseMoveEvent(event);
	}
}

void ScrollAndZoomView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		enableDragging(event->pos());
	} else {
		QGraphicsView::mousePressEvent(event);
	}
}

void ScrollAndZoomView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		disableDragging();
	} else {
		QGraphicsView::mouseReleaseEvent(event);
	}
}

void ScrollAndZoomView::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() & Qt::ControlModifier ) {
		mViewZoomer->wheelZoom(event);
	} else {
		QGraphicsView::wheelEvent(event);
	}
}

void ScrollAndZoomView::scrollTo(const QPoint &pos)
{
	auto delta = pos - mLastPosition;
	scrollByDelta(horizontalScrollBar(), delta.x());
	scrollByDelta(verticalScrollBar(), delta.y());
	mLastPosition = pos;
}

void ScrollAndZoomView::scrollByDelta(QScrollBar *scrollBar, int delta) const
{
	scrollBar->setValue(scrollBar->value() - delta);
}

void ScrollAndZoomView::enableDragging(const QPoint &pos)
{
	mIsDragging = true;
	mLastPosition = pos;
	setDragCursorEnabled(true);
}

void ScrollAndZoomView::disableDragging()
{
	mIsDragging = false;
	mLastPosition = {};
	setDragCursorEnabled(false);
}

void ScrollAndZoomView::setDragCursorEnabled(bool enabled) const
{
	enabled ? QGuiApplication::setOverrideCursor(Qt::SizeAllCursor) : QGuiApplication::restoreOverrideCursor();
}

} // namespace kImageAnnotator

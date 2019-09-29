/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationView.h"

namespace kImageAnnotator {

AnnotationView::AnnotationView(QGraphicsScene *scene) : QGraphicsView(scene)
{
	disableDragging();
}

void AnnotationView::keyPressEvent(QKeyEvent *event)
{
	mKeyHelper.keyPress(event);
	if(mKeyHelper.isSpacePressed()) {
		enableDragging(mapFromGlobal(QCursor::pos()));
	}
	QGraphicsView::keyPressEvent(event);
}

void AnnotationView::keyReleaseEvent(QKeyEvent *event)
{
	mKeyHelper.keyRelease(event);
	if(!mKeyHelper.isSpacePressed()) {
		disableDragging();
	}
	QGraphicsView::keyReleaseEvent(event);
}

void AnnotationView::mouseMoveEvent(QMouseEvent *event)
{
	if(mDragging) {
		scrollTo(event->pos());
		return;
	}
	QGraphicsView::mouseMoveEvent(event);
}

void AnnotationView::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton) {
		enableDragging(event->pos());
		return;
	}
	QGraphicsView::mousePressEvent(event);
}

void AnnotationView::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::MidButton) {
		disableDragging();
		return;
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void AnnotationView::scrollTo(const QPoint &pos)
{
	auto delta = pos - mLastPosition;
	scrollByDelta(horizontalScrollBar(), delta.x());
	scrollByDelta(verticalScrollBar(), delta.y());
	mLastPosition = pos;
}

void AnnotationView::scrollByDelta(QScrollBar *scrollBar, int delta) const
{
	scrollBar->setValue(scrollBar->value() - delta);
}

void AnnotationView::enableDragging(const QPoint &pos)
{
	mDragging = true;
	mLastPosition = pos;
	setDragCursorEnabled(true);
}

void AnnotationView::disableDragging()
{
	mDragging = false;
	mLastPosition = {};
	setDragCursorEnabled(false);
}

void AnnotationView::setDragCursorEnabled(bool enabled) const
{
	enabled ? QGuiApplication::setOverrideCursor(Qt::SizeAllCursor) : QGuiApplication::restoreOverrideCursor();
}

} // namespace kImageAnnotator

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

#include "AnnotationDockWidgetDragHandle.h"

namespace kImageAnnotator {

AnnotationDockWidgetDragHandle::AnnotationDockWidgetDragHandle(QWidget *parent) :
	QWidget(parent),
	mLabel(new QLabel(this)),
	mLayout(new QHBoxLayout(this))
{
	QTransform t;
	t.rotate(90);
	mHorizontalHandlerImage = IconLoader::loadAsPixmap(QLatin1String("dragHandle.svg"));
	mVerticalHandlerImage = mHorizontalHandlerImage.transformed(t);
	
	auto leftMargin = ScaledSizeProvider::scaledWidth(3);
	auto topMargin = ScaledSizeProvider::scaledWidth(5);
	auto rightMargin = 0;
	auto bottomMargin = ScaledSizeProvider::scaledWidth(2);
	mLayout->addWidget(mLabel);
	mLayout->setAlignment(Qt::AlignCenter);
	mLayout->setContentsMargins(leftMargin, topMargin, rightMargin, bottomMargin);

	setCursor(Qt::SizeAllCursor);
	setLayout(mLayout);
}

AnnotationDockWidgetDragHandle::~AnnotationDockWidgetDragHandle()
{
	delete mLabel;
	delete mLayout;
}

QSize AnnotationDockWidgetDragHandle::sizeHint() const
{
	return QWidget::sizeHint();
}

QSize AnnotationDockWidgetDragHandle::minimumSizeHint() const
{
	return QWidget::sizeHint();
}

void AnnotationDockWidgetDragHandle::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
}

void AnnotationDockWidgetDragHandle::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->ignore();
}

void AnnotationDockWidgetDragHandle::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();
}

void AnnotationDockWidgetDragHandle::mousePressEvent(QMouseEvent *event)
{
	event->ignore();
}

void AnnotationDockWidgetDragHandle::mouseReleaseEvent(QMouseEvent *event)
{
	event->ignore();
}

void AnnotationDockWidgetDragHandle::setOrientation(Qt::Orientation orientation)
{
	if (orientation == Qt::Horizontal) {
		mLabel->setPixmap(mHorizontalHandlerImage);
	} else {
		mLabel->setPixmap(mVerticalHandlerImage);
	}
}

} // namespace kImageAnnotator

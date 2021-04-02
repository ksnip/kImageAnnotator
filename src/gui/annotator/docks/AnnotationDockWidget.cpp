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

#include "AnnotationDockWidget.h"

namespace kImageAnnotator {

AnnotationDockWidget::AnnotationDockWidget(AnnotationDockWidgetContent *content) :
	QDockWidget(content->name()),
	mContent(content),
	mDragHandle(new AnnotationDockWidgetDragHandle(this)),
	mVerticalFeatures(features() ^ QDockWidget::DockWidgetFloatable),
	mHorizontalFeatures(QDockWidget::DockWidgetVerticalTitleBar | mVerticalFeatures)
{
	setAllowedAreas(Qt::AllDockWidgetAreas);
	setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);

	setTitleBarWidget(mDragHandle);
	setToolTip(mContent->name());
	setWidget(content);

	connect(this, &QDockWidget::dockLocationChanged, this, &AnnotationDockWidget::updateDockLocation);
}

AnnotationDockWidget::~AnnotationDockWidget()
{
	delete mDragHandle;
}

void AnnotationDockWidget::isVisible(bool isVisible)
{
	setVisible(isVisible);
}

void AnnotationDockWidget::updateDockLocation(Qt::DockWidgetArea area)
{
	if(area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea) {
		mContent->setOrientation(Qt::Horizontal);
		mDragHandle->setOrientation(Qt::Horizontal);
		setFeatures(mHorizontalFeatures);
		resizeToContent();
	} else if (area == Qt::LeftDockWidgetArea || area == Qt::RightDockWidgetArea) {
		mContent->setOrientation(Qt::Vertical);
		mDragHandle->setOrientation(Qt::Vertical);
		setFeatures(mVerticalFeatures);
		resizeToContent();
	} else {
		resizeToDragHandle();
	}
}

void AnnotationDockWidget::resizeToDragHandle()
{
	auto offset = ScaledSizeProvider::scaledSize(QSize(2, 3));
	setFixedSize(mDragHandle->sizeHint() + offset);
}

void AnnotationDockWidget::resizeToContent()
{
	setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
	setMinimumSize(0, 0);
}

} // namespace kImageAnnotator

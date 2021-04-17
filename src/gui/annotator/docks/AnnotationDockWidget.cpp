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

AnnotationDockWidget::AnnotationDockWidget(AbstractAnnotationDockWidgetContent *content) :
	QDockWidget(content->name()),
	mContent(content),
	mDragHandle(new AnnotationDockWidgetDragHandle(this)),
	mVerticalFeatures(features() ^ QDockWidget::DockWidgetFloatable),
	mHorizontalFeatures(QDockWidget::DockWidgetVerticalTitleBar | mVerticalFeatures),
	mWasVisibleBeforeCollapse(isVisible())
{
	setObjectName(content->name());
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

void AnnotationDockWidget::setCollapsed(bool isCollapsed)
{
	if(isCollapsed) {
		mWasVisibleBeforeCollapse = isVisible();
		setVisible(false);
	} else {
		setVisible(mWasVisibleBeforeCollapse);
	}
}

void AnnotationDockWidget::updateDockLocation(Qt::DockWidgetArea area)
{
	if(area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea) {
		setOrientation(Qt::Horizontal, mHorizontalFeatures);
	} else if (area == Qt::LeftDockWidgetArea || area == Qt::RightDockWidgetArea) {
		setOrientation(Qt::Vertical, mVerticalFeatures);
	} else {
		resizeToDragHandle();
	}
}

void AnnotationDockWidget::setOrientation(Qt::Orientation orientation, QDockWidget::DockWidgetFeatures &features)
{
	mContent->setOrientation(orientation);
	mDragHandle->setOrientation(orientation);
	setFeatures(features);
	resizeToContent();
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

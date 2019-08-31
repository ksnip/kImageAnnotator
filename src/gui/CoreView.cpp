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

#include "CoreView.h"

namespace kImageAnnotator {

CoreView::CoreView(Config *config)
{
	mConfig = config;
	mAnnotationArea = new AnnotationArea(mConfig);
	mAnnotationWidget = new AnnotationWidget(mAnnotationArea, mConfig);
	mCropWidget = new CropWidget(mAnnotationArea);
	mScaleWidget = new ScaleWidget(mAnnotationArea);
	addWidget(mAnnotationWidget);
	addWidget(mCropWidget);
	addWidget(mScaleWidget);

	connect(mAnnotationArea, &AnnotationArea::imageChanged, this, &CoreView::imageChanged);
	connect(mCropWidget, &CropWidget::closing, this, &CoreView::showAnnotator);
	connect(mScaleWidget, &ScaleWidget::closing, this, &CoreView::showAnnotator);
}

CoreView::~CoreView()
{
	delete mAnnotationArea;
	delete mAnnotationWidget;
}

QImage CoreView::image() const
{
	return mAnnotationArea->image();
}

void CoreView::loadImage(const QPixmap &pixmap)
{
	mAnnotationArea->loadImage(pixmap);
}

void CoreView::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
    mAnnotationArea->insertImageItem(position, pixmap);
}

void CoreView::showAnnotator()
{
	setCurrentWidget(mAnnotationWidget);
}

void CoreView::showCropper()
{
	setCurrentWidget(mCropWidget);
	mCropWidget->activate();
}

void CoreView::showScaler()
{
	setCurrentWidget(mScaleWidget);
	mScaleWidget->activate();
}

QAction *CoreView::undoAction()
{
	return mAnnotationArea->undoAction();
}

QAction *CoreView::redoAction()
{
	return mAnnotationArea->redoAction();
}

QSize CoreView::sizeHint() const
{
	return mAnnotationWidget->sizeHint();
}

} // namespace kImageAnnotator

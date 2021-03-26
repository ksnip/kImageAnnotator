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

#include "RotateWidget.h"

namespace kImageAnnotator {

RotateWidget::RotateWidget() :
	mAnnotationArea(nullptr),
	mView(new QGraphicsView),
	mMainLayout(new QVBoxLayout(this))
{
	initGui();
}

RotateWidget::~RotateWidget()
{
	delete mMainLayout;
	delete mView;
}

void RotateWidget::activate(AnnotationArea *annotationArea)
{
	Q_ASSERT(annotationArea != nullptr);

	mAnnotationArea = annotationArea;
	mView->setScene(annotationArea);
	showDialog();
}

void RotateWidget::initGui()
{
	mMainLayout->addWidget(mView);
	setLayout(mMainLayout);
}

void RotateWidget::showDialog()
{
	RotateDialog rotateDialog(this);
	connect(&rotateDialog, &RotateDialog::rotate, this, &RotateWidget::rotate);
	connect(&rotateDialog, &RotateDialog::flip, this, &RotateWidget::flip);
	rotateDialog.exec();

	emit closing();
}

void RotateWidget::rotate(qreal angel)
{
	Q_ASSERT(mAnnotationArea != nullptr);

	mAnnotationArea->rotate(angel);
}

void RotateWidget::flip(FlipDirection direction)
{
	Q_ASSERT(mAnnotationArea != nullptr);

	mAnnotationArea->flip(direction);
}

} // namespace kImageAnnotator
/*
 * Copyright (C) 2021 Antonio Prcela <antonio.prcela@gmail.com>
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

#include "AnnotationControlsWidget.h"

namespace kImageAnnotator {

AnnotationControlsWidget::AnnotationControlsWidget() :
	mMainLayout(new QBoxLayout(QBoxLayout::LeftToRight)),
	mControls(new Controls(this))
{
	mMainLayout->addWidget(mControls);
	mMainLayout->setContentsMargins(0, 0, 0, 0);

	connect(mControls, &Controls::undo, this, &AnnotationControlsWidget::controlsUndo);
	connect(mControls, &Controls::redo, this, &AnnotationControlsWidget::controlsRedo);
	connect(mControls, &Controls::crop, this, &AnnotationControlsWidget::controlsCrop);
	connect(mControls, &Controls::scale, this, &AnnotationControlsWidget::controlsScale);
	connect(mControls, &Controls::modifyCanvas, this, &AnnotationControlsWidget::controlsModifyCanvas);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);
}

AnnotationControlsWidget::~AnnotationControlsWidget()
{
}

void AnnotationControlsWidget::setOrientation(Qt::Orientation orientation)
{
	AbstractAnnotationDockWidgetContent::setOrientation(orientation);
}

void AnnotationControlsWidget::controlsUndo() const
{
	emit undo();
}

void AnnotationControlsWidget::controlsRedo() const
{
	emit redo();
}

void AnnotationControlsWidget::controlsCrop() const
{
	emit showCrop();
}

void AnnotationControlsWidget::controlsScale() const
{
	emit showScale();
}

void AnnotationControlsWidget::controlsModifyCanvas() const
{
	emit showModifyCanvas();
}

QString AnnotationControlsWidget::name() const
{
	return tr("Controls");
}

} // namespace kImageAnnotator

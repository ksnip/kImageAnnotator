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

	connect(mControls, &Controls::undo, this, &AnnotationControlsWidget::undo);
	connect(mControls, &Controls::redo, this, &AnnotationControlsWidget::redo);
	connect(mControls, &Controls::crop, this, &AnnotationControlsWidget::showCrop);
	connect(mControls, &Controls::scale, this, &AnnotationControlsWidget::showScale);
	connect(mControls, &Controls::rotate, this, &AnnotationControlsWidget::showRotate);
	connect(mControls, &Controls::modifyCanvas, this, &AnnotationControlsWidget::showModifyCanvas);
	connect(mControls, &Controls::cut, this, &AnnotationControlsWidget::showCut);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);
}

void AnnotationControlsWidget::setOrientation(Qt::Orientation orientation)
{
	AbstractAnnotationDockWidgetContent::setOrientation(orientation);
}

QString AnnotationControlsWidget::name() const
{
	return tr("Controls");
}

} // namespace kImageAnnotator

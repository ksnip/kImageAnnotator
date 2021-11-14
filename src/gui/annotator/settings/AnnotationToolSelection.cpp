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

#include "AnnotationToolSelection.h"

namespace kImageAnnotator {

AnnotationToolSelection::AnnotationToolSelection() :
	mMainLayout(new QVBoxLayout),
	mToolPicker(new ToolPicker(this)),
	mScrollareaToolPicker(new QScrollArea)
{
	mScrollareaToolPicker->setWidgetResizable(true);
	mScrollareaToolPicker->setWidget(mToolPicker);
	mScrollareaToolPicker->setFrameShape(QFrame::NoFrame);
	mMainLayout->addWidget(mScrollareaToolPicker);
	mMainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mToolPicker, &ToolPicker::toolSelected, this, &AnnotationToolSelection::toolTypeChanged);
}

AnnotationToolSelection::~AnnotationToolSelection()
{
	delete mToolPicker;
}

Tools AnnotationToolSelection::toolType() const
{
	return mToolPicker->tool();
}

void AnnotationToolSelection::setToolType(Tools tool)
{
	mToolPicker->setTool(tool);
}

void AnnotationToolSelection::setOrientation(Qt::Orientation orientation)
{
	AbstractAnnotationDockWidgetContent::setOrientation(orientation);
}

QString AnnotationToolSelection::name() const
{
	return tr("Tool Selection");
}

} // namespace kImageAnnotator

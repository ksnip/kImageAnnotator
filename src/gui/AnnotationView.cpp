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

#include "AnnotationView.h"

namespace kImageAnnotator {

AnnotationView::AnnotationView(AnnotationArea *annotationArea, Config *config)
{
	mConfig = config;
	mAnnotationArea = annotationArea;

	initGui();
	setupDefaults();
}

AnnotationView::~AnnotationView()
{
	delete mView;
	delete mMainLayout;
	delete mToolsLayout;
	delete mToolPicker;
	delete mColorPicker;
	delete mTextColorPicker;
	delete mWidthPicker;
	delete mFillTypePicker;
}

QSize AnnotationView::sizeHint() const
{
	auto minWidth = mToolsLayout->sizeHint().width();
	auto minHeight = mToolsLayout->sizeHint().height();
	auto sceneWidth = mAnnotationArea->sceneRect().width();
	auto sceneHeight = mAnnotationArea->sceneRect().height();
	auto width = minWidth + sceneWidth;
	auto height = (minHeight > sceneHeight) ? minHeight : sceneHeight;
	auto offset = QSize(100, 100);
	return QSize(width, height) + offset;
}

void AnnotationView::initGui()
{
	mView = new QGraphicsView(mAnnotationArea);
	mMainLayout = new QHBoxLayout();
	mToolsLayout = new QVBoxLayout();
	mToolPicker = new ToolPicker();
	mColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("tool_color_picker")), tr("Color"));
	mTextColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("format-text-color")), tr("Text Color"));
	mWidthPicker = new SizePicker(QIcon::fromTheme(QStringLiteral("newline")), tr("Width"));
	mFillTypePicker = new FillTypePicker(QIcon::fromTheme(QStringLiteral("fill-color")), tr("Fill Type"));

	mToolsLayout->addWidget(mToolPicker);
	mToolsLayout->addSpacing(20);
	mToolsLayout->addWidget(mColorPicker);
	mToolsLayout->addWidget(mTextColorPicker);
	mToolsLayout->addWidget(mWidthPicker);
	mToolsLayout->addWidget(mFillTypePicker);
	mToolsLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	mMainLayout->addLayout(mToolsLayout);
	mMainLayout->addWidget(mView);

	mVisibilitySwitcher.setOutlineColorWidget(mColorPicker);
	mVisibilitySwitcher.setForegroundColorWidget(mTextColorPicker);
	mVisibilitySwitcher.setSizeWidget(mWidthPicker);
	mVisibilitySwitcher.setFillWidget(mFillTypePicker);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mToolPicker, &ToolPicker::toolSelected, mConfig, &Config::setSelectedTool);
	connect(mToolPicker, &ToolPicker::toolSelected, this, &AnnotationView::updateSelection);
	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationView::setToolColor);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationView::setToolTextColor);
	connect(mWidthPicker, &SizePicker::sizeSelected, this, &AnnotationView::setToolWidth);
	connect(mFillTypePicker, &FillTypePicker::fillSelected, this, &AnnotationView::setToolFillType);
}

void AnnotationView::setupDefaults()
{
	mToolPicker->setTool(mConfig->selectedTool());
}

void AnnotationView::updateSelection(ToolTypes tool)
{
	mColorPicker->setColor(mConfig->toolColor(tool));
	mTextColorPicker->setColor(mConfig->toolTextColor(tool));
	mWidthPicker->setSize(mConfig->toolWidth(tool));
	mFillTypePicker->setFill(mConfig->toolFillType(tool));

	mVisibilitySwitcher.setCurrentTool(tool);
}

void AnnotationView::setToolColor(const QColor &color)
{
	mConfig->setToolColor(color, mToolPicker->tool());
}

void AnnotationView::setToolTextColor(const QColor &color)
{
	mConfig->setToolTextColor(color, mToolPicker->tool());
}

void AnnotationView::setToolWidth(int size)
{
	mConfig->setToolWidth(size, mToolPicker->tool());
}

void AnnotationView::setToolFillType(FillTypes fill)
{
	mConfig->setToolFillType(fill, mToolPicker->tool());
}

} // namespace kImageAnnotator

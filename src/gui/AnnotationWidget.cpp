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

#include "AnnotationWidget.h"

namespace kImageAnnotator {

AnnotationWidget::AnnotationWidget(AnnotationArea *annotationArea, Config *config)
{
	mConfig = config;
	mAnnotationArea = annotationArea;

	initGui();
	loadConfig();
}

AnnotationWidget::~AnnotationWidget()
{
	delete mView;
	delete mMainLayout;
	delete mToolPicker;
	delete mColorPicker;
	delete mWidthPicker;
	delete mTextColorPicker;
	delete mFontSizePicker;
	delete mFillTypePicker;
}

QSize AnnotationWidget::sizeHint() const
{
	auto minWidth = mToolLayout->sizeHint().width();
	auto minHeight = mToolLayout->sizeHint().height();
	auto sceneWidth = mAnnotationArea->sceneRect().width();
	auto sceneHeight = mAnnotationArea->sceneRect().height();
	auto width = minWidth + sceneWidth;
	auto height = (minHeight > sceneHeight) ? minHeight : sceneHeight;
	auto offset = QSize(100, 100);
	return QSize(width, height) + offset;
}

void AnnotationWidget::initGui()
{
	mView = new QGraphicsView(mAnnotationArea);
	mMainLayout = new QHBoxLayout();
	mToolLayout = new QVBoxLayout();
	mToolPicker = new ToolPicker();
	mColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("tool_color_picker")), tr("Color"));
	mWidthPicker = new SizePicker(QIcon::fromTheme(QStringLiteral("newline")), tr("Width"));
	mTextColorPicker = new ColorPicker(QIcon::fromTheme(QStringLiteral("format-text-color")), tr("Text Color"));
	mFontSizePicker = new SizePicker(QIcon::fromTheme(QStringLiteral("font-size-up")), tr("Font Size"));
	mFontSizePicker->setRange(10, 40);
	mFillTypePicker = new FillTypePicker(QIcon::fromTheme(QStringLiteral("fill-color")), tr("Fill Type"));

	mToolLayout->addWidget(mToolPicker);
	mToolLayout->addSpacing(20);
	mToolLayout->addWidget(mColorPicker);
	mToolLayout->addWidget(mWidthPicker);
	mToolLayout->addWidget(mTextColorPicker);
	mToolLayout->addWidget(mFontSizePicker);
	mToolLayout->addWidget(mFillTypePicker);
	mToolLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	mMainLayout->addLayout(mToolLayout);
	mMainLayout->addWidget(mView);

	mVisibilitySwitcher.setOutlineColorWidget(mColorPicker);
	mVisibilitySwitcher.setForegroundColorWidget(mTextColorPicker);
	mVisibilitySwitcher.setSizeWidget(mWidthPicker);
	mVisibilitySwitcher.setFillWidget(mFillTypePicker);
	mVisibilitySwitcher.setFontSizeWidget(mFontSizePicker);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mToolPicker, &ToolPicker::toolSelected, mConfig, &Config::setSelectedTool);
	connect(mToolPicker, &ToolPicker::toolSelected, this, &AnnotationWidget::updateSelection);
	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationWidget::setToolColor);
	connect(mWidthPicker, &SizePicker::sizeSelected, this, &AnnotationWidget::setToolWidth);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationWidget::setToolTextColor);
	connect(mFontSizePicker, &SizePicker::sizeSelected, this, &AnnotationWidget::setToolFontSize);
	connect(mFillTypePicker, &FillTypePicker::fillSelected, this, &AnnotationWidget::setToolFillType);
	connect(mConfig, &Config::loaded, this, &AnnotationWidget::loadConfig);
}

void AnnotationWidget::loadConfig()
{
	mToolPicker->setTool(mConfig->selectedTool());
}

void AnnotationWidget::updateSelection(ToolTypes tool)
{
	mColorPicker->setColor(mConfig->toolColor(tool));
	mTextColorPicker->setColor(mConfig->toolTextColor(tool));
	mWidthPicker->setSize(mConfig->toolWidth(tool));
	mFillTypePicker->setFill(mConfig->toolFillType(tool));
	mFontSizePicker->setSize(mConfig->toolFontSize(tool));
	mVisibilitySwitcher.setCurrentTool(tool);
}

void AnnotationWidget::setToolColor(const QColor &color)
{
	mConfig->setToolColor(color, mToolPicker->tool());
}

void AnnotationWidget::setToolTextColor(const QColor &color)
{
	mConfig->setToolTextColor(color, mToolPicker->tool());
}

void AnnotationWidget::setToolWidth(int size)
{
	mConfig->setToolWidth(size, mToolPicker->tool());
}

void AnnotationWidget::setToolFillType(FillTypes fill)
{
	mConfig->setToolFillType(fill, mToolPicker->tool());
}

void AnnotationWidget::setToolFontSize(int size)
{
	mConfig->setToolFontSize(size, mToolPicker->tool());
}

} // namespace kImageAnnotator

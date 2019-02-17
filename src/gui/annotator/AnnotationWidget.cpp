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
	delete mFirstNumberPicker;
}

QSize AnnotationWidget::sizeHint() const
{
	auto minSize = mToolLayout->sizeHint();
	auto sceneSize = mAnnotationArea->sceneRect().size();
	auto width = minSize.width() + sceneSize.width();
	auto height = (minSize.height() > sceneSize.height()) ? minSize.height() : sceneSize.height();
	auto offset = QSize(100, 100);
	return QSize(static_cast<int>(width), static_cast<int>(height)) + offset;
}

void AnnotationWidget::initGui()
{
	mView = new QGraphicsView(mAnnotationArea);
	mMainLayout = new QHBoxLayout();
	mToolLayout = new QVBoxLayout();
	mToolPicker = new ToolPicker();
	mColorPicker = new ColorPicker(IconLoader::load(QStringLiteral("color.svg")), tr("Color"));
	mWidthPicker = new NumberPicker(IconLoader::load(QStringLiteral("width.svg")), tr("Width"));
	mTextColorPicker = new ColorPicker(IconLoader::load(QStringLiteral("textColor.svg")), tr("Text Color"));
	mFontSizePicker = new NumberPicker(IconLoader::load(QStringLiteral("fontSize.svg")), tr("Font Size"));
	mFontSizePicker->setRange(10, 40);
	mFillTypePicker = new FillTypePicker(IconLoader::load(QStringLiteral("fillType.svg")), tr("Border And Fill Visibility"));
	mFirstNumberPicker = new NumberPicker(IconLoader::load(QStringLiteral("number.svg")), tr("Starting Number"));
	mFirstNumberPicker->setRange(1, 100);

	mToolLayout->addWidget(mToolPicker);
	mToolLayout->addSpacing(20);
	mToolLayout->addWidget(mColorPicker);
	mToolLayout->addWidget(mWidthPicker);
	mToolLayout->addWidget(mTextColorPicker);
	mToolLayout->addWidget(mFontSizePicker);
	mToolLayout->addWidget(mFillTypePicker);
	mToolLayout->addWidget(mFirstNumberPicker);
	mToolLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

	mMainLayout->addLayout(mToolLayout);
	mMainLayout->addWidget(mView);

	mWidgetConfigurator.setColorWidget(mColorPicker);
	mWidgetConfigurator.setTextColorWidget(mTextColorPicker);
	mWidgetConfigurator.setWidthWidget(mWidthPicker);
	mWidgetConfigurator.setFillTypeWidget(mFillTypePicker);
	mWidgetConfigurator.setFontSizeWidget(mFontSizePicker);
	mWidgetConfigurator.setFirstNumberWidget(mFirstNumberPicker);

	setLayout(mMainLayout);

	setFocusPolicy(Qt::ClickFocus);

	connect(mToolPicker, &ToolPicker::toolSelected, mConfig, &Config::setSelectedTool);
	connect(mToolPicker, &ToolPicker::toolSelected, this, &AnnotationWidget::updateSelection);
	connect(mColorPicker, &ColorPicker::colorSelected, this, &AnnotationWidget::setToolColor);
	connect(mWidthPicker, &NumberPicker::numberSelected, this, &AnnotationWidget::setToolWidth);
	connect(mTextColorPicker, &ColorPicker::colorSelected, this, &AnnotationWidget::setToolTextColor);
	connect(mFontSizePicker, &NumberPicker::numberSelected, this, &AnnotationWidget::setToolFontSize);
	connect(mFillTypePicker, &FillTypePicker::fillSelected, this, &AnnotationWidget::setToolFillType);
	connect(mFirstNumberPicker, &NumberPicker::numberSelected, this, &AnnotationWidget::setFirstBadgeNumber);
	connect(mConfig, &Config::loaded, this, &AnnotationWidget::loadConfig);
	connect(mConfig, &Config::toolChanged, mToolPicker, &ToolPicker::setTool);
}

void AnnotationWidget::loadConfig()
{
	mToolPicker->setTool(mConfig->selectedTool());
}

void AnnotationWidget::updateSelection(ToolTypes tool)
{
	mColorPicker->setColor(mConfig->toolColor(tool));
	mTextColorPicker->setColor(mConfig->toolTextColor(tool));
	mWidthPicker->setNumber(mConfig->toolWidth(tool));
	mFillTypePicker->setFillType(mConfig->toolFillType(tool));
	mFontSizePicker->setNumber(mConfig->toolFontSize(tool));
	mWidgetConfigurator.setCurrentTool(tool);
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

void AnnotationWidget::setFirstBadgeNumber(int number)
{
	mConfig->setFirstBadgeNumber(number);
}

} // namespace kImageAnnotator

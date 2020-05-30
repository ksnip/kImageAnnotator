/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "WidgetConfigurator.h"

namespace kImageAnnotator {

WidgetConfigurator::WidgetConfigurator() :
	mColorWidget(nullptr),
	mTextColorWidget(nullptr),
	mWidthWidget(nullptr),
	mFillTypeWidget(nullptr),
	mFontSizeWidget(nullptr),
	mFirstNumberWidget(nullptr),
	mBlurRadiusWidget(nullptr),
	mStickerWidget(nullptr)
{
	mCurrentTool = ToolTypes::Select;
}

void WidgetConfigurator::setCurrentTool(ToolTypes tool)
{
	if (mCurrentTool == tool) {
		return;
	}

	mCurrentTool = tool;
	updateWidgets();
}

void WidgetConfigurator::setColorWidget(ColorPicker *widget)
{
	mColorWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setTextColorWidget(ColorPicker *widget)
{
	mTextColorWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setWidthWidget(NumberPicker *widget)
{
	mWidthWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setFillTypeWidget(FillTypePicker *widget)
{
	mFillTypeWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setFontSizeWidget(NumberPicker *widget)
{
	mFontSizeWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setFirstNumberWidget(NumberPicker *widget)
{
	mFirstNumberWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setBlurRadiusWidget(NumberPicker *widget)
{
	mBlurRadiusWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::setStickerWidget(StickerPicker *widget)
{
	mStickerWidget = widget;
	updateWidgets();
}

void WidgetConfigurator::updateWidgets() const
{
	updateProperties();
	updateVisibility();
}

void WidgetConfigurator::updateProperties() const
{
	switch (mCurrentTool) {
		case ToolTypes::Text:
		case ToolTypes::Number:
			setNoFillAndNoBorderVisible(true);
			break;
		default:
			setNoFillAndNoBorderVisible(false);
	}
}

void WidgetConfigurator::updateVisibility() const
{
	switch (mCurrentTool) {
		case ToolTypes::Select:
		case ToolTypes::Image:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Pen:
		case ToolTypes::MarkerPen:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::MarkerRect:
		case ToolTypes::MarkerEllipse:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Line:
		case ToolTypes::Arrow:
		case ToolTypes::DoubleArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Ellipse:
		case ToolTypes::Rect:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Number:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::NumberPointer:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Text:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Blur:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(true);
			setStickerWidgetVisible(false);
			break;
		case ToolTypes::Sticker:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setBlurRadiusWidgetVisible(false);
			setStickerWidgetVisible(true);
			break;
		default:
			qCritical("Unknown tooltype in WidgetConfigurator");
	}
}

void WidgetConfigurator::setColorWidgetVisible(bool enabled) const
{
	if (mColorWidget) {
		mColorWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setTextColorWidgetVisible(bool enabled) const
{
	if (mTextColorWidget) {
		mTextColorWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setWidthWidgetVisible(bool enabled) const
{
	if (mWidthWidget) {
		mWidthWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setFillWidgetVisible(bool enabled) const
{
	if (mFillTypeWidget) {
		mFillTypeWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setFontSizeWidgetVisible(bool enabled) const
{
	if (mFontSizeWidget) {
		mFontSizeWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setFirstNumberWidgetVisible(bool enabled) const
{
	if (mFirstNumberWidget) {
		mFirstNumberWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setNoFillAndNoBorderVisible(bool enabled) const
{
	if (mFillTypeWidget) {
		if (enabled) {
			mFillTypeWidget->addNoFillAndNoBorderToList();
		} else {
			mFillTypeWidget->removeNoFillAndNoBorderToList();
		}
	}
}

void WidgetConfigurator::setBlurRadiusWidgetVisible(bool enabled) const
{
	if (mBlurRadiusWidget) {
		mBlurRadiusWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setStickerWidgetVisible(bool enabled) const
{
	if (mStickerWidget) {
		mStickerWidget->setVisible(enabled);
	}
}

} // namespace kImageAnnotator

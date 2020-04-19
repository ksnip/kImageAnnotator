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

WidgetConfigurator::WidgetConfigurator()
{
	mColorWidget = nullptr;
	mTextColorWidget = nullptr;
	mWidthWidget = nullptr;
	mFillTypeWidget = nullptr;
	mFontSizeWidget = nullptr;
	mFirstNumberWidget = nullptr;
	mBlurRadiusWidget = nullptr;

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
			setNoFillAndNoBorderEnabled(true);
			break;
		default:
			setNoFillAndNoBorderEnabled(false);
	}
}

void WidgetConfigurator::updateVisibility() const
{
	switch (mCurrentTool) {
		case ToolTypes::Select:
		case ToolTypes::Image:
			setColorWidgetEnabled(false);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(false);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Pen:
		case ToolTypes::MarkerPen:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(true);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::MarkerRect:
		case ToolTypes::MarkerEllipse:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(false);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Line:
		case ToolTypes::Arrow:
		case ToolTypes::DoubleArrow:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(true);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Ellipse:
		case ToolTypes::Rect:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(true);
			setFillWidgetEnabled(true);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Number:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(true);
			setWidthWidgetEnabled(true);
			setFillWidgetEnabled(true);
			setFontSizeWidgetEnabled(true);
			setFirstNumberWidgetEnabled(true);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Text:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(true);
			setWidthWidgetEnabled(true);
			setFillWidgetEnabled(true);
			setFontSizeWidgetEnabled(true);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(false);
			break;
		case ToolTypes::Blur:
			setColorWidgetEnabled(false);
			setTextColorWidgetEnabled(false);
			setWidthWidgetEnabled(false);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			setFirstNumberWidgetEnabled(false);
			setBlurRadiusWidgetEnabled(true);
			break;
		default:
			qCritical("Unknown tooltype in WidgetConfigurator");
	}
}

void WidgetConfigurator::setColorWidgetEnabled(bool enabled) const
{
	if (mColorWidget) {
		mColorWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setTextColorWidgetEnabled(bool enabled) const
{
	if (mTextColorWidget) {
		mTextColorWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setWidthWidgetEnabled(bool enabled) const
{
	if (mWidthWidget) {
		mWidthWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setFillWidgetEnabled(bool enabled) const
{
	if (mFillTypeWidget) {
		mFillTypeWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setFontSizeWidgetEnabled(bool enabled) const
{
	if (mFontSizeWidget) {
		mFontSizeWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setFirstNumberWidgetEnabled(bool enabled) const
{
	if (mFirstNumberWidget) {
		mFirstNumberWidget->setEnabled(enabled);
	}
}

void WidgetConfigurator::setNoFillAndNoBorderEnabled(bool enabled) const
{
	if (mFillTypeWidget == nullptr) {
		return;
	}

	if (enabled) {
		mFillTypeWidget->addNoFillAndNoBorderToList();
	} else {
		mFillTypeWidget->removeNoFillAndNoBorderToList();
	}
}

void WidgetConfigurator::setBlurRadiusWidgetEnabled(bool enabled) const
{
	if (mBlurRadiusWidget) {
		mBlurRadiusWidget->setEnabled(enabled);
	}
}

} // namespace kImageAnnotator

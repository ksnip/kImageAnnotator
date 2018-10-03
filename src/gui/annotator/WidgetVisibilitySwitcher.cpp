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

#include "WidgetVisibilitySwitcher.h"

namespace kImageAnnotator {

WidgetVisibilitySwitcher::WidgetVisibilitySwitcher()
{
	mColorWidget = nullptr;
	mTextColorWidget = nullptr;
	mWidthWidget = nullptr;
	mFillWidget = nullptr;
	mFontSizeWidget = nullptr;

	mCurrentTool = ToolTypes::Select;
}

void WidgetVisibilitySwitcher::setCurrentTool(ToolTypes tool)
{
	if (mCurrentTool == tool) {
		return;
	}

	mCurrentTool = tool;
	updateVisibility();
}

void WidgetVisibilitySwitcher::setOutlineColorWidget(QWidget *widget)
{
	mColorWidget = widget;
	updateVisibility();
}

void WidgetVisibilitySwitcher::setForegroundColorWidget(QWidget *widget)
{
	mTextColorWidget = widget;
	updateVisibility();
}

void WidgetVisibilitySwitcher::setSizeWidget(QWidget *widget)
{
	mWidthWidget = widget;
	updateVisibility();
}

void WidgetVisibilitySwitcher::setFillWidget(QWidget *widget)
{
	mFillWidget = widget;
	updateVisibility();
}

void WidgetVisibilitySwitcher::setFontSizeWidget(QWidget *widget)
{
	mFontSizeWidget = widget;
	updateVisibility();
}

void WidgetVisibilitySwitcher::updateVisibility()
{
	switch (mCurrentTool) {
		case ToolTypes::Select:
			setColorWidgetEnabled(false);
			setTextColorWidgetEnabled(false);
			setSizeWidgetEnabled(false);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			break;
		case ToolTypes::Pen:
		case ToolTypes::Marker:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setSizeWidgetEnabled(true);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			break;
		case ToolTypes::Line:
		case ToolTypes::Arrow:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setSizeWidgetEnabled(true);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(false);
			break;
		case ToolTypes::Ellipse:
		case ToolTypes::Rect:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(false);
			setSizeWidgetEnabled(true);
			setFillWidgetEnabled(true);
			setFontSizeWidgetEnabled(false);
			break;
		case ToolTypes::Number:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(true);
			setSizeWidgetEnabled(true);
			setFillWidgetEnabled(false);
			setFontSizeWidgetEnabled(true);
		case ToolTypes::Text:
			setColorWidgetEnabled(true);
			setTextColorWidgetEnabled(true);
			setSizeWidgetEnabled(true);
			setFillWidgetEnabled(true);
			setFontSizeWidgetEnabled(true);
			break;
		default:
			qCritical("Unknown tooltype in WidgetVisibilitySwitcher");
	}
}

void WidgetVisibilitySwitcher::setColorWidgetEnabled(bool enabled)
{
	if (mColorWidget) {
		mColorWidget->setEnabled(enabled);
	}
}

void WidgetVisibilitySwitcher::setTextColorWidgetEnabled(bool enabled)
{
	if (mTextColorWidget) {
		mTextColorWidget->setEnabled(enabled);
	}
}

void WidgetVisibilitySwitcher::setSizeWidgetEnabled(bool enabled)
{
	if (mWidthWidget) {
		mWidthWidget->setEnabled(enabled);
	}
}

void WidgetVisibilitySwitcher::setFillWidgetEnabled(bool enabled)
{
	if (mFillWidget) {
		mFillWidget->setEnabled(enabled);
	}
}

void WidgetVisibilitySwitcher::setFontSizeWidgetEnabled(bool enabled)
{
	if (mFontSizeWidget) {
		mFontSizeWidget->setEnabled(enabled);
	}
}

} // namespace kImageAnnotator

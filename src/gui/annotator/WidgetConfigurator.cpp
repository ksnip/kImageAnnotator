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
	mFillModeWidget(nullptr),
	mFontSizeWidget(nullptr),
	mFirstNumberWidget(nullptr),
	mObfuscateFactorWidget(nullptr),
	mStickerWidget(nullptr)
{
	mCurrentTool = Tools::Select;
}

void WidgetConfigurator::setCurrentTool(Tools tool)
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

void WidgetConfigurator::setFillTypeWidget(FillModePicker *widget)
{
	mFillModeWidget = widget;
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

void WidgetConfigurator::setObfuscateFactorWidget(NumberPicker *widget)
{
	mObfuscateFactorWidget = widget;
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
		case Tools::Text:
		case Tools::Number:
		case Tools::NumberArrow:
			setNoFillAndNoBorderVisible(true);
			break;
		default:
			setNoFillAndNoBorderVisible(false);
	}
}

void WidgetConfigurator::updateVisibility() const
{
	switch (mCurrentTool) {
		case Tools::Select:
		case Tools::Image:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Pen:
		case Tools::MarkerPen:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Line:
		case Tools::Arrow:
		case Tools::DoubleArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Ellipse:
		case Tools::Rect:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Number:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::NumberPointer:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::NumberArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Text:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::TextPointer:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			break;
		case Tools::Blur:
		case Tools::Pixelate:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(true);
			setStickerWidgetVisible(false);
			break;
		case Tools::Sticker:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFontSizeWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
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
	if (mFillModeWidget) {
		mFillModeWidget->setVisible(enabled);
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
	if (mFillModeWidget) {
		if (enabled) {
			mFillModeWidget->addNoFillAndNoBorderToList();
		} else {
			mFillModeWidget->removeNoFillAndNoBorderToList();
		}
	}
}

void WidgetConfigurator::setObfuscateFactorWidgetVisible(bool enabled) const
{
	if (mObfuscateFactorWidget) {
		mObfuscateFactorWidget->setVisible(enabled);
	}
}

void WidgetConfigurator::setStickerWidgetVisible(bool enabled) const
{
	if (mStickerWidget) {
		mStickerWidget->setVisible(enabled);
	}
}

} // namespace kImageAnnotator

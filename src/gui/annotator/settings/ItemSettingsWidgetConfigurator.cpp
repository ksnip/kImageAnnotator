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

#include "ItemSettingsWidgetConfigurator.h"

namespace kImageAnnotator {

ItemSettingsWidgetConfigurator::ItemSettingsWidgetConfigurator() :
	mColorWidget(nullptr),
	mTextColorWidget(nullptr),
	mWidthWidget(nullptr),
	mFillModeWidget(nullptr),
	mFirstNumberWidget(nullptr),
	mObfuscateFactorWidget(nullptr),
	mStickerWidget(nullptr),
	mShadowPicker(nullptr),
	mFontPicker(nullptr),
	mOpacityPicker(nullptr)
{
	mCurrentTool = Tools::Select;
}

void ItemSettingsWidgetConfigurator::setCurrentTool(Tools tool)
{
	if (mCurrentTool == tool) {
		return;
	}

	mCurrentTool = tool;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setColorWidget(ColorPicker *widget)
{
	mColorWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setTextColorWidget(ColorPicker *widget)
{
	mTextColorWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setWidthWidget(NumberPicker *widget)
{
	mWidthWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setFillTypeWidget(FillModePicker *widget)
{
	mFillModeWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setFirstNumberWidget(NumberPicker *widget)
{
	mFirstNumberWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setObfuscateFactorWidget(NumberPicker *widget)
{
	mObfuscateFactorWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setStickerWidget(StickerPicker *widget)
{
	mStickerWidget = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setShadowWidget(BoolPicker *widget)
{
	mShadowPicker = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setFontWidget(FontPicker *widget)
{
	mFontPicker = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::setOpacityWidget(NumberPicker *widget)
{
	mOpacityPicker = widget;
	updateWidgets();
}

void ItemSettingsWidgetConfigurator::updateWidgets() const
{
	updateProperties();
	updateVisibility();
}

void ItemSettingsWidgetConfigurator::updateProperties() const
{
	switch (mCurrentTool) {
		case Tools::Text:
		case Tools::Number:
		case Tools::NumberArrow:
			setNoFillAndNoBorderVisible(true);
			break;
		case Tools::MarkerPen:
			setWidthRange(1, 100);
			break;
		default:
			setNoFillAndNoBorderVisible(false);
			setWidthRange(1, 20);
	}
}

void ItemSettingsWidgetConfigurator::updateVisibility() const
{
	switch (mCurrentTool) {
		case Tools::Select:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(false);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(false);
			break;
		case Tools::Image:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
		case Tools::Pen:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
		case Tools::MarkerPen:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(false);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(false);
			break;
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(false);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(false);
			break;
		case Tools::Line:
		case Tools::Arrow:
		case Tools::DoubleArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
		case Tools::Ellipse:
		case Tools::Rect:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
		case Tools::Number:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::NumberPointer:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::NumberArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFirstNumberWidgetVisible(true);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::Text:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::TextPointer:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::TextArrow:
			setColorWidgetVisible(true);
			setTextColorWidgetVisible(true);
			setWidthWidgetVisible(true);
			setFillWidgetVisible(true);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(true);
			setOpacityWidgetVisible(true);
			break;
		case Tools::Blur:
		case Tools::Pixelate:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(true);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(false);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(false);
			break;
		case Tools::Sticker:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(true);
			setShadowWidgetVisible(true);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
	case Tools::Duplicate:
			setColorWidgetVisible(false);
			setTextColorWidgetVisible(false);
			setWidthWidgetVisible(false);
			setFillWidgetVisible(false);
			setFirstNumberWidgetVisible(false);
			setObfuscateFactorWidgetVisible(false);
			setStickerWidgetVisible(false);
			setShadowWidgetVisible(false);
			setFontWidgetVisible(false);
			setOpacityWidgetVisible(true);
			break;
		default:
			qCritical("Unknown tool type in WidgetConfigurator");
	}
}

void ItemSettingsWidgetConfigurator::setColorWidgetVisible(bool enabled) const
{
	if (mColorWidget) {
		mColorWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setTextColorWidgetVisible(bool enabled) const
{
	if (mTextColorWidget) {
		mTextColorWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setWidthWidgetVisible(bool enabled) const
{
	if (mWidthWidget) {
		mWidthWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setFillWidgetVisible(bool enabled) const
{
	if (mFillModeWidget) {
		mFillModeWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setFirstNumberWidgetVisible(bool enabled) const
{
	if (mFirstNumberWidget) {
		mFirstNumberWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setNoFillAndNoBorderVisible(bool enabled) const
{
	if (mFillModeWidget) {
		if (enabled) {
			mFillModeWidget->addNoFillAndNoBorderToList();
		} else {
			mFillModeWidget->removeNoFillAndNoBorderToList();
		}
	}
}

void ItemSettingsWidgetConfigurator::setObfuscateFactorWidgetVisible(bool enabled) const
{
	if (mObfuscateFactorWidget) {
		mObfuscateFactorWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setStickerWidgetVisible(bool enabled) const
{
	if (mStickerWidget) {
		mStickerWidget->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setShadowWidgetVisible(bool enabled) const
{
	if (mShadowPicker) {
		mShadowPicker->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setFontWidgetVisible(bool enabled) const
{
	if (mFontPicker) {
		mFontPicker->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setOpacityWidgetVisible(bool enabled) const
{
	if (mOpacityPicker) {
		mOpacityPicker->setVisible(enabled);
	}
}

void ItemSettingsWidgetConfigurator::setWidthRange(int min, int max) const
{
	if (mWidthWidget) {
		mWidthWidget->setRange(min, max);
	}
}

} // namespace kImageAnnotator

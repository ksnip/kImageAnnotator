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

#include "Config.h"

namespace kImageAnnotator {

Config::Config() :
	mSelectTool(Tools::Pen),
	mItemShadowEnabled(false),
	mSmoothPathEnabled(false),
	mSaveToolSelection(false),
	mSmoothFactor(0),
	mSwitchToSelectToolAfterDrawingItem(false),
	mNumberUpdateMode(NumberUpdateMode::UpdateOnlyNewNumbers)
{
	mAllTools = QList<Tools>{
		Tools::Pen,
		Tools::MarkerPen,
		Tools::MarkerRect,
		Tools::MarkerEllipse,
		Tools::Line,
		Tools::Arrow,
		Tools::DoubleArrow,
		Tools::Rect,
		Tools::Ellipse,
		Tools::Number,
		Tools::NumberPointer,
		Tools::NumberArrow,
		Tools::Text,
		Tools::TextPointer,
		Tools::TextArrow,
		Tools::Blur,
		Tools::Pixelate,
		Tools::Image,
		Tools::Sticker,
		Tools::Duplicate
	};
	initGeneralSettings();
	initToolSettings();
}

Tools Config::selectedTool() const
{
	return mSelectTool;
}

void Config::setSelectedToolType(Tools tool)
{
	if (selectedTool() == tool) {
		return;
	}

	mSelectTool = tool;
	saveToolType(tool);
}

QColor Config::toolColor(Tools tool) const
{
	return mToolToColor[tool];
}

void Config::setToolColor(const QColor &color, Tools tool)
{
	if (toolColor(tool) == color) {
		return;
	}

	mToolToColor[tool] = color;
	saveToolColor(tool, color);
}

QColor Config::toolTextColor(Tools tool) const
{
	return mToolToTextColor[tool];
}

void Config::setToolTextColor(const QColor &color, Tools tool)
{
	if (toolTextColor(tool) == color) {
		return;
	}

	mToolToTextColor[tool] = color;
	saveToolTextColor(tool, color);
}

int Config::toolWidth(Tools tool) const
{
	return mToolToWidth[tool];
}

void Config::setToolWidth(int size, Tools tool)
{
	if (toolWidth(tool) == size) {
		return;
	}

	mToolToWidth[tool] = size;
	saveToolWidth(tool, size);
}

FillModes Config::toolFillType(Tools tool) const
{
	return mToolToFillType[tool];
}

void Config::setToolFillType(FillModes fillType, Tools tool)
{
	if (toolFillType(tool) == fillType) {
		return;
	}

	mToolToFillType[tool] = fillType;
	saveToolFillType(tool, fillType);
}

QFont Config::toolFont(Tools toolType) const
{
	return mToolToFont[toolType];
}

void Config::setToolFont(const QFont &font, Tools toolType)
{
	auto tmpFont = font;
	tmpFont.setPointSize(toolFontSize(toolType));
	if (toolFont(toolType) == tmpFont) {
		return;
	}

	mToolToFont[toolType] = tmpFont;
}

int Config::toolFontSize(Tools toolType) const
{
	return mToolToFont[toolType].pointSize();
}

void Config::setToolFontSize(int fontSize, Tools toolType)
{
	if (toolFontSize(toolType) == fontSize) {
		return;
	}

	mToolToFont[toolType].setPointSize(fontSize);
	saveToolFontSize(toolType, fontSize);
}

bool Config::itemShadowEnabled() const
{
	return mItemShadowEnabled;
}

void Config::setItemShadowEnabled(bool enabled)
{
	mItemShadowEnabled = enabled;
}

bool Config::smoothPathEnabled() const
{
	return mSmoothPathEnabled;
}

void Config::setSmoothPathEnabled(bool enabled)
{
	mSmoothPathEnabled = enabled;
}

void Config::setSaveToolSelection(bool enabled)
{
	if (mSaveToolSelection == enabled) {
		return;
	}

	mSaveToolSelection = enabled;
	initToolSettings();
}

int Config::smoothFactor() const
{
	return mSmoothFactor;
}

void Config::setSmoothFactor(int factor)
{
	mSmoothFactor = factor;
}

bool Config::switchToSelectToolAfterDrawingItem() const
{
	return mSwitchToSelectToolAfterDrawingItem;
}

void Config::setSwitchToSelectToolAfterDrawingItem(bool enabled)
{
	mSwitchToSelectToolAfterDrawingItem = enabled;
}

NumberUpdateMode Config::numberUpdateMode() const
{
	return mNumberUpdateMode;
}

void Config::setNumberToolUpdateMode(enum NumberUpdateMode numberUpdateMode)
{
	if (numberUpdateMode != mNumberUpdateMode) {
		mNumberUpdateMode = numberUpdateMode;
		emit numberUpdateModeChanged(numberUpdateMode);
	}
}

int Config::obfuscationFactor(Tools toolType) const
{
	return mToolToObfuscationFactor[toolType];
}

void Config::setObfuscationFactor(int factor, Tools toolType)
{
	if (obfuscationFactor(toolType) == factor) {
		return;
	}

	mToolToObfuscationFactor[toolType] = factor;
	saveObfuscateFactor(toolType, factor);
}

QColor Config::canvasColor() const
{
	return mCanvasColor;
}

void Config::setCanvasColor(const QColor &color)
{
	mCanvasColor = color;
}

// Private Methods

void Config::initToolSettings()
{
	initSelectedTool();
	initToolColors();
	initToolTextColors();
	initToolWidths();
	initToolFillTypes();
	initToolFonts();
	initObfuscateFactor();
}

void Config::initSelectedTool()
{
	mSelectTool = loadToolType();
};

void Config::initToolColors()
{
	for (auto toolType : mAllTools) {
		mToolToColor[toolType] = loadToolColor(toolType);
	}
}

void Config::initToolTextColors()
{
	for (auto toolType : mAllTools) {
		mToolToTextColor[toolType] = loadToolTextColor(toolType);
	}
}

void Config::initToolWidths()
{
	for (auto toolType : mAllTools) {
		mToolToWidth[toolType] = loadToolWidth(toolType);
	}
}

void Config::initToolFillTypes()
{
	for (auto toolType : mAllTools) {
		mToolToFillType[toolType] = loadToolFillType(toolType);
	}
}

void Config::initToolFonts()
{
	auto textFont = QFont(QLatin1String("Times"), loadToolFontSize(Tools::Text), QFont::Bold);
	auto numberFont = QFont(QLatin1String("Helvetica"), loadToolFontSize(Tools::Number), QFont::Bold);
	mToolToFont[Tools::Text] = textFont;
	mToolToFont[Tools::TextPointer] = textFont;
	mToolToFont[Tools::TextArrow] = textFont;
	mToolToFont[Tools::Number] = numberFont;
	mToolToFont[Tools::NumberPointer] = numberFont;
	mToolToFont[Tools::NumberArrow] = numberFont;
}

void Config::initObfuscateFactor()
{
	for (auto toolType : mAllTools) {
		mToolToObfuscationFactor[toolType] = loadObfuscateFactor(toolType);
	}
}

void Config::initGeneralSettings()
{
	mSaveToolSelection = false;
	mSmoothPathEnabled = true;
	mItemShadowEnabled = true;
	mSmoothFactor = 7;
	mSwitchToSelectToolAfterDrawingItem = false;
	mNumberUpdateMode = NumberUpdateMode::UpdateOnlyNewNumbers;
	mCanvasColor = Qt::white;
}

QColor Config::loadToolColor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolColor(toolType), defaultToolColor(toolType)).value<QColor>();
	} else {
		return defaultToolColor(toolType);
	}
}

void Config::saveToolColor(Tools toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolColor(toolType), color);
		mConfig.sync();
	}
}

QColor Config::loadToolTextColor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolTextColor(toolType), defaultToolTextColor(toolType)).value<QColor>();
	} else {
		return defaultToolTextColor(toolType);
	}
}

void Config::saveToolTextColor(Tools toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolTextColor(toolType), color);
		mConfig.sync();
	}
}

int Config::loadToolWidth(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolWidth(toolType), defaultToolWidth(toolType)).value<int>();
	} else {
		return defaultToolWidth(toolType);
	}
}

void Config::saveToolWidth(Tools toolType, int size)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolWidth(toolType), size);
		mConfig.sync();
	}
}

FillModes Config::loadToolFillType(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolFillType(toolType), static_cast<int>(defaultToolFillMode(toolType))).value<FillModes>();
	} else {
		return defaultToolFillMode(toolType);
	}
}

void Config::saveToolFillType(Tools toolType, FillModes fillType)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolFillType(toolType), static_cast<int>(fillType));
		mConfig.sync();
	}
}

Tools Config::loadToolType()
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolType(), static_cast<int>(defaultToolType())).value<Tools>();
	} else {
		return defaultToolType();
	}
}

void Config::saveToolType(Tools toolType)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolType(), static_cast<int>(toolType));
		mConfig.sync();
	}
}

int Config::loadToolFontSize(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolFontSize(toolType), defaultToolFontSize(toolType)).value<int>();
	} else {
		return defaultToolFontSize(toolType);
	}
}

void Config::saveToolFontSize(Tools toolType, int fontSize)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolFontSize(toolType), fontSize);
		mConfig.sync();
	}
}

int Config::loadObfuscateFactor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::obfuscateFactor(toolType), defaultObfuscateFactor()).value<int>();
	} else {
		return defaultObfuscateFactor();
	}
}

void Config::saveObfuscateFactor(Tools toolType, int radius)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::obfuscateFactor(toolType), radius);
		mConfig.sync();
	}
}

QColor Config::defaultToolColor(Tools toolType)
{
	switch (toolType) {
		case Tools::MarkerPen:
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
			return { Qt::yellow };
		case Tools::Line:
			return { Qt::blue };
		case Tools::Rect:
			return { Qt::gray };
		case Tools::Text:
			return { Qt::black };
		case Tools::Blur:
		case Tools::Pixelate:
			return { Qt::white };
		case Tools::Duplicate:
			return { Qt::green };
		default:
			return { Qt::red };
	}
}

QColor Config::defaultToolTextColor(Tools toolType)
{
	switch (toolType) {
		case Tools::Text:
		case Tools::TextPointer:
		case Tools::TextArrow:
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
			return { Qt::white };
		default:
			return { Qt::blue };
	}
}

int Config::defaultToolWidth(Tools toolType)
{
	switch (toolType) {
		case Tools::MarkerPen:
			return 10;
		case Tools::Arrow:
		case Tools::DoubleArrow:
			return 6;
		case Tools::Number:
			return 5;
		case Tools::Text:
		case Tools::TextArrow:
			return 2;
		case Tools::NumberPointer:
		case Tools::TextPointer:
		case Tools::Duplicate:
			return 1;
		default:
			return 3;
	}
}

FillModes Config::defaultToolFillMode(Tools toolType)
{
	switch (toolType) {
		case Tools::Arrow:
		case Tools::DoubleArrow:
		case Tools::Rect:
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::Blur:
		case Tools::Pixelate:
		case Tools::TextPointer:
		case Tools::Image:
		case Tools::Sticker:
			return FillModes::BorderAndFill;
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
		case Tools::Duplicate:
			return FillModes::NoBorderAndFill;
		case Tools::NumberArrow:
		case Tools::TextArrow:
			return FillModes::NoBorderAndNoFill;
		default:
			return FillModes::BorderAndNoFill;
	}
}

Tools Config::defaultToolType()
{
	return Tools::Pen;
}

int Config::defaultToolFontSize(Tools toolType)
{
	switch (toolType) {
		case Tools::Text:
		case Tools::TextPointer:
		case Tools::TextArrow:
			return 15;
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
			return 20;
		default:
			return 10;
	}
}

int Config::defaultObfuscateFactor()
{
	return 10;
}

} // namespace kImageAnnotator

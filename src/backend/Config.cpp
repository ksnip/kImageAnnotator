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

Config::Config()
{
	mAllTools = QList<ToolTypes>{
		ToolTypes::Pen,
		ToolTypes::MarkerPen,
		ToolTypes::MarkerRect,
		ToolTypes::MarkerEllipse,
		ToolTypes::Line,
		ToolTypes::Arrow,
		ToolTypes::DoubleArrow,
		ToolTypes::Rect,
		ToolTypes::Ellipse,
		ToolTypes::Number,
		ToolTypes::NumberPointer,
		ToolTypes::Text,
		ToolTypes::Blur,
		ToolTypes::Pixelate,
		ToolTypes::Image
	};
	initGeneralSettings();
	initToolSettings();
}

ToolTypes Config::selectedTool() const
{
	return mSelectTool;
}

void Config::setSelectedToolType(ToolTypes tool)
{
	if (selectedTool() == tool) {
		return;
	}

	mSelectTool = tool;
	saveToolType(tool);
}

QColor Config::toolColor(ToolTypes tool) const
{
	return mToolToColor[tool];
}

void Config::setToolColor(const QColor &color, ToolTypes tool)
{
	if (toolColor(tool) == color) {
		return;
	}

	mToolToColor[tool] = color;
	saveToolColor(tool, color);
}

QColor Config::toolTextColor(ToolTypes tool) const
{
	return mToolToTextColor[tool];
}

void Config::setToolTextColor(const QColor &color, ToolTypes tool)
{
	if (toolTextColor(tool) == color) {
		return;
	}

	mToolToTextColor[tool] = color;
	saveToolTextColor(tool, color);
}

int Config::toolWidth(ToolTypes tool) const
{
	return mToolToWidth[tool];
}

void Config::setToolWidth(int size, ToolTypes tool)
{
	if (toolWidth(tool) == size) {
		return;
	}

	mToolToWidth[tool] = size;
	saveToolWidth(tool, size);
}

FillTypes Config::toolFillType(ToolTypes tool) const
{
	return mToolToFillType[tool];
}

void Config::setToolFillType(FillTypes fillType, ToolTypes tool)
{
	if (toolFillType(tool) == fillType) {
		return;
	}

	mToolToFillType[tool] = fillType;
	saveToolFillType(tool, fillType);
}

QFont Config::toolFont(ToolTypes toolType) const
{
	return mToolToFont[toolType];
}

void Config::setToolFont(const QFont &font, ToolTypes toolType)
{
	auto tmpFont = font;
	tmpFont.setPointSize(toolFontSize(toolType));
	if (toolFont(toolType) == tmpFont) {
		return;
	}

	mToolToFont[toolType] = tmpFont;
}

int Config::toolFontSize(ToolTypes toolType) const
{
	return mToolToFont[toolType].pointSize();
}

void Config::setToolFontSize(int fontSize, ToolTypes toolType)
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

int Config::obfuscationFactor(ToolTypes toolType) const
{
	return mToolToObfuscationFactor[toolType];
}

void Config::setObfuscationFactor(int factor, ToolTypes toolType)
{
	if (obfuscationFactor(toolType) == factor) {
		return;
	}

	mToolToObfuscationFactor[toolType] = factor;
	saveObfuscateFactor(toolType, factor);
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
	mToolToFont[ToolTypes::Text] = QFont(QStringLiteral("Times"), loadToolFontSize(ToolTypes::Text), QFont::Bold);
	mToolToFont[ToolTypes::Number] = QFont(QStringLiteral("Helvetica"), loadToolFontSize(ToolTypes::Number), QFont::Bold);
	mToolToFont[ToolTypes::NumberPointer] = QFont(QStringLiteral("Helvetica"), loadToolFontSize(ToolTypes::NumberPointer), QFont::Bold);
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
}

QColor Config::loadToolColor(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolColor(toolType), defaultToolColor(toolType)).value<QColor>();
	} else {
		return defaultToolColor(toolType);
	}
}

void Config::saveToolColor(ToolTypes toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolColor(toolType), color);
		mConfig.sync();
	}
}

QColor Config::loadToolTextColor(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolTextColor(toolType), defaultToolTextColor(toolType)).value<QColor>();
	} else {
		return defaultToolTextColor(toolType);
	}
}

void Config::saveToolTextColor(ToolTypes toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolTextColor(toolType), color);
		mConfig.sync();
	}
}

int Config::loadToolWidth(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolWidth(toolType), defaultToolWidth(toolType)).value<int>();
	} else {
		return defaultToolWidth(toolType);
	}
}

void Config::saveToolWidth(ToolTypes toolType, int size)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolWidth(toolType), size);
		mConfig.sync();
	}
}

FillTypes Config::loadToolFillType(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolFillType(toolType), static_cast<int>(defaultToolFillType(toolType))).value<FillTypes>();
	} else {
		return defaultToolFillType(toolType);
	}
}

void Config::saveToolFillType(ToolTypes toolType, FillTypes fillType)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolFillType(toolType), static_cast<int>(fillType));
		mConfig.sync();
	}
}

ToolTypes Config::loadToolType()
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolType(), static_cast<int>(defaultToolType())).value<ToolTypes>();
	} else {
		return defaultToolType();
	}
}

void Config::saveToolType(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolType(), static_cast<int>(toolType));
		mConfig.sync();
	}
}

int Config::loadToolFontSize(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::toolFontSize(toolType), defaultToolFontSize(toolType)).value<int>();
	} else {
		return defaultToolFontSize(toolType);
	}
}

void Config::saveToolFontSize(ToolTypes toolType, int fontSize)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::toolFontSize(toolType), fontSize);
		mConfig.sync();
	}
}

int Config::loadObfuscateFactor(ToolTypes toolType)
{
	if (mSaveToolSelection) {
		return mConfig.value(ConfigNameHelper::obfuscateFactor(toolType), defaultObfuscateFactor()).value<int>();
	} else {
		return defaultObfuscateFactor();
	}
}

void Config::saveObfuscateFactor(ToolTypes toolType, int radius)
{
	if (mSaveToolSelection) {
		mConfig.setValue(ConfigNameHelper::obfuscateFactor(toolType), radius);
		mConfig.sync();
	}
}

QColor Config::defaultToolColor(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::MarkerPen:
		case ToolTypes::MarkerRect:
		case ToolTypes::MarkerEllipse:
			return { Qt::yellow };
		case ToolTypes::Line:
			return { Qt::blue };
		case ToolTypes::Rect:
			return { Qt::gray };
		case ToolTypes::Text:
			return { Qt::black };
		case ToolTypes::Blur:
		case ToolTypes::Pixelate:
			return { Qt::white };
		default:
			return { Qt::red };
	}
}

QColor Config::defaultToolTextColor(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Text:
		case ToolTypes::Number:
		case ToolTypes::NumberPointer:
			return { Qt::white };
		default:
			return { Qt::blue };
	}
}

int Config::defaultToolWidth(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::MarkerPen:
			return 10;
		case ToolTypes::Arrow:
		case ToolTypes::DoubleArrow:
			return 6;
		case ToolTypes::Number:
			return 5;
		case ToolTypes::Text:
			return 2;
		default:
			return 3;
	}
}

FillTypes Config::defaultToolFillType(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Arrow:
		case ToolTypes::DoubleArrow:
		case ToolTypes::Rect:
		case ToolTypes::Number:
		case ToolTypes::NumberPointer:
		case ToolTypes::Blur:
		case ToolTypes::Pixelate:
			return FillTypes::BorderAndFill;
		case ToolTypes::MarkerRect:
		case ToolTypes::MarkerEllipse:
		case ToolTypes::Image:
			return FillTypes::NoBorderAndFill;
		default:
			return FillTypes::BorderAndNoFill;
	}
}

ToolTypes Config::defaultToolType()
{
	return ToolTypes::Pen;
}

int Config::defaultToolFontSize(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Text:
			return 15;
		case ToolTypes::Number:
		case ToolTypes::NumberPointer:
			return 20;
		default:
			return 10;
	}
}

int Config::defaultObfuscateFactor() const
{
	return 10;
}

} // namespace kImageAnnotator

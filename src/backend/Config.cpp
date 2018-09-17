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

#include "Config.h"

namespace kImageAnnotator {

Config::Config()
{
	mAllTools = QList<ToolTypes>{
		ToolTypes::Pen,
		ToolTypes::Marker,
		ToolTypes::Line,
		ToolTypes::Arrow,
		ToolTypes::Rect,
		ToolTypes::Ellipse,
		ToolTypes::Number,
		ToolTypes::Text
	};
	initGeneralSettings();
	initToolSettings();
}

ToolTypes Config::selectedTool() const
{
	return mSelectTool;
}

void Config::setSelectedTool(ToolTypes tool)
{
	if (selectedTool() == tool) {
		return;
	}

	mSelectTool = tool;
	saveToolType(tool);
	emit toolChanged(tool);
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

// Private Methodes

void Config::initToolSettings()
{
	initSelectedTool();
	initToolColors();
	initToolTextColors();
	initToolWidths();
	initToolFillTypes();
	initToolFonts();
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

QColor Config::defaultToolColor(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Pen:
			return { Qt::red };
		case ToolTypes::Marker:
			return { Qt::yellow };
		case ToolTypes::Line:
			return { Qt::blue };
		case ToolTypes::Arrow:
			return { Qt::red };
		case ToolTypes::Rect:
			return { Qt::gray };
		case ToolTypes::Ellipse:
			return { Qt::red };
		case ToolTypes::Number:
			return { Qt::red };
		case ToolTypes::Text:
			return { Qt::black };
		default:
			return { Qt::red };
	}
}

QColor Config::defaultToolTextColor(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Text:
		case ToolTypes::Number:
			return { Qt::white };
		default:
			return { Qt::blue };
	}
}

int Config::defaultToolWidth(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Pen:
			return 3;
		case ToolTypes::Marker:
			return 10;
		case ToolTypes::Line:
			return 3;
		case ToolTypes::Arrow:
			return 6;
		case ToolTypes::Rect:
			return 3;
		case ToolTypes::Ellipse:
			return 3;
		case ToolTypes::Number:
			return 5;
		case ToolTypes::Text:
			return 10;
		default:
			return 3;
	}
}

FillTypes Config::defaultToolFillType(ToolTypes toolType) const
{

	switch (toolType) {
		case ToolTypes::Pen:
			return FillTypes::NoFill;
		case ToolTypes::Marker:
			return FillTypes::NoFill;
		case ToolTypes::Line:
			return FillTypes::NoFill;
		case ToolTypes::Arrow:
			return FillTypes::Fill;
		case ToolTypes::Rect:
			return FillTypes::NoFill;
		case ToolTypes::Ellipse:
			return FillTypes::NoFill;
		case ToolTypes::Number:
			return FillTypes::Fill;
		case ToolTypes::Text:
			return FillTypes::NoFill;
		default:
			return FillTypes::NoFill;
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
			return 20;
		default:
			return 10;
	}
}

} // namespace kImageAnnotator

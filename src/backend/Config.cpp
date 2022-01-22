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

#include <QGuiApplication>
#include "Config.h"

namespace kImageAnnotator {

Config::Config(const QSharedPointer<ISettings> &settings) :
	mSettings(settings),
	mSelectTool(Tools::Pen),
	mSmoothPathEnabled(false),
	mSaveToolSelection(false),
	mSmoothFactor(0),
	mSwitchToSelectToolAfterDrawingItem(true),
	mSelectItemAfterDrawing(true),
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

void Config::setToolWidth(int width, Tools tool)
{
	if (toolWidth(tool) == width) {
		return;
	}

	mToolToWidth[tool] = width;
	saveToolWidth(tool, width);
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

QFont Config::toolFont(Tools tool) const
{
	return mToolToFont[tool];
}

void Config::setToolFont(const QFont &font, Tools tool)
{
	if (toolFont(tool) == font) {
		return;
	}

	mToolToFont[tool] = font;
	saveToolFont(tool, font);
}

bool Config::shadowEnabled(Tools tool) const
{
	return mToolToShadowEnabled[tool];
}

void Config::setShadowEnabled(bool enabled, Tools tool)
{
	if (shadowEnabled(tool) == enabled) {
		return;
	}

	mToolToShadowEnabled[tool] = enabled;
	saveToolShadowEnabled(tool, enabled);
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
	saveToolObfuscateFactor(toolType, factor);
}

QColor Config::canvasColor() const
{
	return mCanvasColor;
}

void Config::setCanvasColor(const QColor &color)
{
	mCanvasColor = color;
}

QByteArray Config::annotatorDockWidgetsState() const
{
	return mSettings->value(ConfigNameHelper::annotatorDockWidgetsState(), QVariant()).toByteArray();
}

void Config::setAnnotatorDockWidgetsState(const QByteArray &state)
{
	mSettings->setValue(ConfigNameHelper::annotatorDockWidgetsState(), state);
	mSettings->sync();
}

bool Config::selectItemAfterDrawing() const
{
	return mSelectItemAfterDrawing;
}

void Config::setSelectItemAfterDrawing(bool enabled)
{
	mSelectItemAfterDrawing = enabled;
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
	initShadowEnabled();
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
	for (auto toolType : mAllTools) {
		mToolToFont[toolType] = loadToolFont(toolType);
	}
}

void Config::initObfuscateFactor()
{
	for (auto toolType : mAllTools) {
		mToolToObfuscationFactor[toolType] = loadToolObfuscateFactor(toolType);
	}
}

void Config::initShadowEnabled()
{
	for (auto toolType : mAllTools) {
		mToolToShadowEnabled[toolType] = loadToolShadowEnabled(toolType);
	}
}

void Config::initGeneralSettings()
{
	mSaveToolSelection = false;
	mSmoothPathEnabled = true;
	mSmoothFactor = 7;
	mSwitchToSelectToolAfterDrawingItem = false;
	mSelectItemAfterDrawing = true;
	mNumberUpdateMode = NumberUpdateMode::UpdateOnlyNewNumbers;
	mCanvasColor = Qt::white;
}

QColor Config::loadToolColor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolColor(toolType), defaultToolColor(toolType)).value<QColor>();
	} else {
		return defaultToolColor(toolType);
	}
}

void Config::saveToolColor(Tools toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolColor(toolType), color);
		mSettings->sync();
	}
}

QColor Config::loadToolTextColor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolTextColor(toolType), defaultToolTextColor(toolType)).value<QColor>();
	} else {
		return defaultToolTextColor(toolType);
	}
}

void Config::saveToolTextColor(Tools toolType, const QColor &color)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolTextColor(toolType), color);
		mSettings->sync();
	}
}

int Config::loadToolWidth(Tools toolType)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolWidth(toolType), defaultToolWidth(toolType)).value<int>();
	} else {
		return defaultToolWidth(toolType);
	}
}

void Config::saveToolWidth(Tools toolType, int size)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolWidth(toolType), size);
		mSettings->sync();
	}
}

FillModes Config::loadToolFillType(Tools toolType)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolFillType(toolType), static_cast<int>(defaultToolFillMode(toolType))).value<FillModes>();
	} else {
		return defaultToolFillMode(toolType);
	}
}

void Config::saveToolFillType(Tools toolType, FillModes fillType)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolFillType(toolType), static_cast<int>(fillType));
		mSettings->sync();
	}
}

QFont Config::loadToolFont(Tools tool) const
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolFont(tool), defaultToolFont(tool)).value<QFont>();
	} else {
		return defaultToolFont(tool);
	}
}

void Config::saveToolFont(Tools tool, const QFont &font)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolFont(tool), font);
		mSettings->sync();
	}
}

Tools Config::loadToolType()
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::toolType(), static_cast<int>(defaultToolType())).value<Tools>();
	} else {
		return defaultToolType();
	}
}

void Config::saveToolType(Tools toolType)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::toolType(), static_cast<int>(toolType));
		mSettings->sync();
	}
}

int Config::loadToolObfuscateFactor(Tools toolType)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::obfuscateFactor(toolType), defaultObfuscateFactor()).value<int>();
	} else {
		return defaultObfuscateFactor();
	}
}

void Config::saveToolObfuscateFactor(Tools toolType, int radius)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::obfuscateFactor(toolType), radius);
		mSettings->sync();
	}
}

bool Config::loadToolShadowEnabled(Tools tool)
{
	if (mSaveToolSelection) {
		return mSettings->value(ConfigNameHelper::shadowEnabled(tool), defaultShadowEnabled(tool)).toBool();
	} else {
		return defaultShadowEnabled(tool);
	}
}

void Config::saveToolShadowEnabled(Tools tool, bool enabled)
{
	if (mSaveToolSelection) {
		mSettings->setValue(ConfigNameHelper::shadowEnabled(tool), enabled);
		mSettings->sync();
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
			return 30;
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

QFont Config::defaultToolFont(Tools tool)
{
	auto textFont = QFont(QGuiApplication::font().family(), 15, QFont::Bold);
    auto numberFont = QFont(QGuiApplication::font().family(), 20, QFont::Bold);

	switch (tool) {
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
			return numberFont;
		case Tools::Text:
		case Tools::TextPointer:
		case Tools::TextArrow:
		default:
			return textFont;
	}
}

Tools Config::defaultToolType()
{
	return Tools::Pen;
}

int Config::defaultObfuscateFactor()
{
	return 10;
}

bool Config::defaultShadowEnabled(Tools tool)
{
	switch (tool) {
		case Tools::Pen:
		case Tools::Line:
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
		case Tools::Arrow:
		case Tools::DoubleArrow:
		case Tools::Rect:
		case Tools::Ellipse:
		case Tools::Sticker:
			return true;
		case Tools::Text:
		case Tools::TextPointer:
		case Tools::TextArrow:
		case Tools::Blur:
		case Tools::Pixelate:
		case Tools::MarkerPen:
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
		case Tools::Duplicate:
		case Tools::Image:
		case Tools::Select:
		default:
			return false;
	}
}

} // namespace kImageAnnotator

/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationSettingsAdapter.h"

namespace kImageAnnotator {

AnnotationSettingsAdapter::AnnotationSettingsAdapter(
		AnnotationGeneralSettings *generalSettings,
		AnnotationItemSettings *itemSettings,
		AnnotationToolSelection *toolSettings,
		AnnotationImageSettings *imageSettings,
		Config *config) :
	mGeneralSettings(generalSettings),
	mItemSettings(itemSettings),
	mToolSettings(toolSettings),
	mImageSettings(imageSettings),
	mConfig(config),
	mEditExistingItem(false)
{
	connect(mToolSettings, &AnnotationToolSelection::toolTypeChanged, this, &AnnotationSettingsAdapter::toolTypeChanged);

	connect(mImageSettings, &AnnotationImageSettings::effectChanged, this, &AnnotationSettingsAdapter::effectChanged);

	connect(mGeneralSettings, &AnnotationGeneralSettings::zoomValueChanged, this, &AnnotationSettingsAdapter::zoomValueChanged);

	connect(mItemSettings, &AnnotationItemSettings::toolColorChanged, this, &AnnotationSettingsAdapter::toolColorChanged);
	connect(mItemSettings, &AnnotationItemSettings::toolWidthChanged, this, &AnnotationSettingsAdapter::toolWidthChanged);
	connect(mItemSettings, &AnnotationItemSettings::toolTextColorChanged, this, &AnnotationSettingsAdapter::toolTextColorChanged);
	connect(mItemSettings, &AnnotationItemSettings::toolFontSizeChanged, this, &AnnotationSettingsAdapter::toolFontSizeChanged);
	connect(mItemSettings, &AnnotationItemSettings::toolFillTypeChanged, this, &AnnotationSettingsAdapter::toolFillTypeChanged);
	connect(mItemSettings, &AnnotationItemSettings::notifyNumberToolSeedChanged, this, &AnnotationSettingsAdapter::notifyNumberToolSeedChanged);
	connect(mItemSettings, &AnnotationItemSettings::obfuscateFactorChanged, this, &AnnotationSettingsAdapter::obfuscateFactorChanged);
	connect(mItemSettings, &AnnotationItemSettings::stickerChanged, this, &AnnotationSettingsAdapter::stickerChanged);
	connect(mItemSettings, &AnnotationItemSettings::shadowEnabledChanged, this, &AnnotationSettingsAdapter::shadowEnabledChanged);

	reloadConfig();
}

void AnnotationSettingsAdapter::editItem(AbstractAnnotationItem *item)
{
	activateSelectTool();
	loadFromItem(item);
	mEditExistingItem = true;
}

void AnnotationSettingsAdapter::activateSelectTool()
{
	mToolSettings->setToolType(Tools::Select);
	mItemSettings->setUpForTool(Tools::Select);
}

Tools AnnotationSettingsAdapter::toolType() const
{
	return mToolSettings->toolType();
}

QColor AnnotationSettingsAdapter::toolColor() const
{
	return mItemSettings->toolColor();
}

QColor AnnotationSettingsAdapter::textColor() const
{
	return mItemSettings->textColor();
}

int AnnotationSettingsAdapter::toolWidth() const
{
	return mItemSettings->toolWidth();
}

int AnnotationSettingsAdapter::fontSize() const
{
	return mItemSettings->fontSize();
}

FillModes AnnotationSettingsAdapter::fillType() const
{
	return mItemSettings->fillMode();
}

int AnnotationSettingsAdapter::obfuscationFactor() const
{
	return mItemSettings->obfuscationFactor();
}

QString AnnotationSettingsAdapter::sticker() const
{
	return mItemSettings->sticker();
}

ImageEffects AnnotationSettingsAdapter::effect() const
{
	return mImageSettings->effect();
}

bool AnnotationSettingsAdapter::shadowEnabled() const
{
	return mItemSettings->shadowEnabled();
}

void AnnotationSettingsAdapter::updateNumberToolSeed(int numberToolSeed)
{
	mItemSettings->updateNumberToolSeed(numberToolSeed);
}

void AnnotationSettingsAdapter::updateZoomLevel(double value)
{
	mGeneralSettings->updateZoomLevel(value);
}

void AnnotationSettingsAdapter::reloadConfig()
{
	mToolSettings->setToolType(mConfig->selectedTool());
	mImageSettings->setEffect(ImageEffects::NoEffect);
	mItemSettings->setUpForTool(toolType());
}

void AnnotationSettingsAdapter::effectChanged(ImageEffects effect)
{
	AbstractSettingsProvider::effectChanged(effect);
}

void AnnotationSettingsAdapter::zoomValueChanged(double value)
{
	AbstractSettingsProvider::zoomValueChanged(value);
}

void AnnotationSettingsAdapter::loadFromConfig(Tools tool)
{
	mItemSettings->setUpForTool(tool);
	mItemSettings->setToolColor(mConfig->toolColor(tool));
	mItemSettings->setTextColor(mConfig->toolTextColor(tool));
	mItemSettings->setToolWidth(mConfig->toolWidth(tool));
	mItemSettings->setFillMode(mConfig->toolFillType(tool));
	mItemSettings->setFontSize(mConfig->toolFontSize(tool));
	mItemSettings->setObfuscationFactor(mConfig->obfuscationFactor(tool));
	mItemSettings->setShadowEnabled(mConfig->shadowEnabled(tool));
}

void AnnotationSettingsAdapter::loadFromItem(const AbstractAnnotationItem *item)
{
	auto properties = item->properties();
	mItemSettings->setUpForTool(item->toolType());
	mItemSettings->setToolColor(properties->color());
	mItemSettings->setTextColor(properties->textColor());
	mItemSettings->setToolWidth(properties->width());
	mItemSettings->setFillMode(properties->fillType());
	mItemSettings->setShadowEnabled(properties->shadowEnabled());

	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();
	if(textProperties != nullptr) {
		mItemSettings->setFontSize(textProperties->font().pointSize());
	}

	auto obfuscateProperties = properties.dynamicCast<AnnotationObfuscateProperties>();
	if(obfuscateProperties != nullptr) {
		mItemSettings->setObfuscationFactor(obfuscateProperties->factor());
	}
}

void AnnotationSettingsAdapter::toolTypeChanged(Tools toolType)
{
	mEditExistingItem = false;
	mConfig->setSelectedToolType(toolType);
	if(!mEditExistingItem) {
		loadFromConfig(toolType);
	}
	toolChanged(toolType);
}

void AnnotationSettingsAdapter::toolColorChanged(const QColor &color)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolColor(color, toolType());
	}
}

void AnnotationSettingsAdapter::toolTextColorChanged(const QColor &color)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolTextColor(color, toolType());
	}
}

void AnnotationSettingsAdapter::toolWidthChanged(int width)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolWidth(width, toolType());
	}
}

void AnnotationSettingsAdapter::toolFillTypeChanged(FillModes fill)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolFillType(fill, toolType());
	}
}

void AnnotationSettingsAdapter::toolFontSizeChanged(int size)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setToolFontSize(size, toolType());
	}
}

void AnnotationSettingsAdapter::notifyNumberToolSeedChanged(int newNumberToolSeed)
{
	numberToolSeedChanged(newNumberToolSeed);
}

void AnnotationSettingsAdapter::obfuscateFactorChanged(int factor)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setObfuscationFactor(factor, toolType());
	}
}

void AnnotationSettingsAdapter::stickerChanged(const QString &sticker)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	}
}

void AnnotationSettingsAdapter::shadowEnabledChanged(bool enabled)
{
	if(mEditExistingItem) {
		itemSettingChanged();
	} else {
		mConfig->setShadowEnabled(enabled, toolType());
	}
}

} // namespace kImageAnnotator

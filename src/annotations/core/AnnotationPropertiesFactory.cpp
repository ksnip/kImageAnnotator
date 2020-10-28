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

#include "AnnotationPropertiesFactory.h"

namespace kImageAnnotator {

AnnotationPropertiesFactory::AnnotationPropertiesFactory(Config *config, AbstractSettingsProvider *settingsProvider) :
	mConfig(config),
	mSettingsProvider(settingsProvider)
{
	Q_ASSERT(mConfig != nullptr);
	Q_ASSERT(mSettingsProvider != nullptr);
}

PropertiesPtr AnnotationPropertiesFactory::create(Tools toolType) const
{
	auto properties = createPropertiesObject(toolType);

	setColor(properties, toolType);
	setTextColor(properties);
	setWidthSize(properties, toolType);
	setFill(properties, toolType);
	setShadowEnabled(properties, toolType);
	setPathProperties(properties);
	setTextProperties(properties, toolType);
	setObfuscateProperties(properties);
	setStickerProperties(properties);

	return properties;
}

PropertiesPtr AnnotationPropertiesFactory::createPropertiesObject(Tools toolType) const
{
	switch (toolType) {
		case Tools::Pen:
		case Tools::MarkerPen:
			return PropertiesPtr(new AnnotationPathProperties());
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
		case Tools::Text:
			return PropertiesPtr(new AnnotationTextProperties());
		case Tools::Blur:
		case Tools::Pixelate:
			return PropertiesPtr(new AnnotationObfuscateProperties());
		case Tools ::Sticker:
			return PropertiesPtr(new AnnotationStickerProperties());
		default:
			return PropertiesPtr(new AnnotationProperties());
	}
}

void AnnotationPropertiesFactory::setColor(const PropertiesPtr &properties, Tools toolType) const
{
	auto color = mSettingsProvider->toolColor();

	if (isMarkerTool(toolType)) {
		color.setAlpha(60);
	}

	properties->setColor(color);
}

void AnnotationPropertiesFactory::setTextColor(const PropertiesPtr &properties) const
{
	properties->setTextColor(mSettingsProvider->textColor());
}

void AnnotationPropertiesFactory::setWidthSize(const PropertiesPtr &properties, Tools toolType) const
{
	switch (toolType) {
		case Tools::NumberPointer:
			properties->setWidth(1);
			break;
		case Tools::MarkerPen:
			properties->setWidth(mSettingsProvider->toolWidth() * 3);
			break;
		default:
			properties->setWidth(mSettingsProvider->toolWidth());
	}
}

void AnnotationPropertiesFactory::setFill(const PropertiesPtr &properties, Tools toolType) const
{
	switch (toolType) {
		case Tools::MarkerPen:
			properties->setFillType(FillModes::BorderAndNoFill);
			break;
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
			properties->setFillType(FillModes::NoBorderAndFill);
			break;
		case Tools::Image:
		case Tools::Sticker:
		case Tools::NumberPointer:
			properties->setFillType(FillModes::BorderAndFill);
			break;
		default:
			properties->setFillType(mSettingsProvider->fillType());
	}
}

void AnnotationPropertiesFactory::setShadowEnabled(const PropertiesPtr &properties, Tools toolType) const
{
	if (isObfuscateTool(toolType) || isMarkerTool(toolType) || toolType == Tools::Image) {
		properties->setShadowEnabled(false);
	} else {
		properties->setShadowEnabled(mConfig->itemShadowEnabled());
	}
}

void AnnotationPropertiesFactory::setPathProperties(const PropertiesPtr &properties) const
{
	auto pathProperties = properties.dynamicCast<AnnotationPathProperties>();
	if (pathProperties != nullptr) {
		pathProperties->setSmoothPathEnabled(mConfig->smoothPathEnabled());
		pathProperties->setSmoothFactor(mConfig->smoothFactor());
	}
}

void AnnotationPropertiesFactory::setTextProperties(const PropertiesPtr &properties, Tools toolType) const
{
	auto textProperties = properties.dynamicCast<AnnotationTextProperties>();
	if (textProperties != nullptr) {
		auto font = mConfig->toolFont(toolType);
		font.setPointSize(mSettingsProvider->fontSize());
		textProperties->setFont(font);
	}
}

void AnnotationPropertiesFactory::setObfuscateProperties(const PropertiesPtr &properties) const
{
	auto obfuscateProperties = properties.dynamicCast<AnnotationObfuscateProperties>();
	if (obfuscateProperties != nullptr) {
		obfuscateProperties->setFactor(mSettingsProvider->obfuscationFactor());
	}
}

void AnnotationPropertiesFactory::setStickerProperties(const PropertiesPtr &properties) const
{
	auto stickerProperties = properties.dynamicCast<AnnotationStickerProperties>();
	if (stickerProperties != nullptr) {
		stickerProperties->setPath(mSettingsProvider->sticker());
	}
}

bool AnnotationPropertiesFactory::isMarkerTool(Tools toolType)
{
	return toolType == Tools::MarkerPen || toolType == Tools::MarkerRect || toolType == Tools::MarkerEllipse;
}

bool AnnotationPropertiesFactory::isObfuscateTool(const Tools &toolType)
{
	return toolType == Tools::Blur || toolType == Tools::Pixelate;
}

} // namespace kImageAnnotator

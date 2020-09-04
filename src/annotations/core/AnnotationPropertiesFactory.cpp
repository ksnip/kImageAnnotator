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

PropertiesPtr AnnotationPropertiesFactory::create(ToolTypes toolType) const
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

PropertiesPtr AnnotationPropertiesFactory::createPropertiesObject(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Pen:
		case ToolTypes::MarkerPen:
			return PropertiesPtr(new AnnotationPathProperties());
		case ToolTypes::Number:
		case ToolTypes::NumberPointer:
		case ToolTypes::Text:
			return PropertiesPtr(new AnnotationTextProperties());
		case ToolTypes::Blur:
		case ToolTypes::Pixelate:
			return PropertiesPtr(new AnnotationObfuscateProperties());
		case ToolTypes ::Sticker:
			return PropertiesPtr(new AnnotationStickerProperties());
		default:
			return PropertiesPtr(new AnnotationProperties());
	}
}

void AnnotationPropertiesFactory::setColor(const PropertiesPtr &properties, ToolTypes toolType) const
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

void AnnotationPropertiesFactory::setWidthSize(const PropertiesPtr &properties, ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::NumberPointer:
			properties->setWidth(1);
			break;
		case ToolTypes::MarkerPen:
			properties->setWidth(mSettingsProvider->toolWidth() * 3);
			break;
		default:
			properties->setWidth(mSettingsProvider->toolWidth());
	}
}

void AnnotationPropertiesFactory::setFill(const PropertiesPtr &properties, ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::MarkerPen:
			properties->setFillType(FillTypes::BorderAndNoFill);
			break;
		case ToolTypes::MarkerRect:
		case ToolTypes::MarkerEllipse:
			properties->setFillType(FillTypes::NoBorderAndFill);
			break;
		case ToolTypes::Image:
		case ToolTypes::Sticker:
		case ToolTypes::NumberPointer:
			properties->setFillType(FillTypes::BorderAndFill);
			break;
		default:
			properties->setFillType(mSettingsProvider->fillType());
	}
}

void AnnotationPropertiesFactory::setShadowEnabled(const PropertiesPtr &properties, ToolTypes toolType) const
{
	if (isObfuscateTool(toolType) || isMarkerTool(toolType) || toolType == ToolTypes::Image) {
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

void AnnotationPropertiesFactory::setTextProperties(const PropertiesPtr &properties, ToolTypes toolType) const
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

bool AnnotationPropertiesFactory::isMarkerTool(ToolTypes toolType) const
{
	return toolType == ToolTypes::MarkerPen || toolType == ToolTypes::MarkerRect || toolType == ToolTypes::MarkerEllipse;
}

bool AnnotationPropertiesFactory::isObfuscateTool(const ToolTypes &toolType) const
{
	return toolType == ToolTypes::Blur || toolType == ToolTypes::Pixelate;
}

} // namespace kImageAnnotator

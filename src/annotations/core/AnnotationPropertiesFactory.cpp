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

AnnotationPropertiesFactory::AnnotationPropertiesFactory(Config *config, AbstractSettingsProvider *settingsProvider)
{
	mConfig = config;
	mSettingsProvider = settingsProvider;
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
	setBlurProperties(properties);
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
		case ToolTypes::Text:
			return PropertiesPtr(new AnnotationTextProperties());
		case ToolTypes::Blur:
			return PropertiesPtr(new AnnotationBlurProperties());
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
	auto width = mSettingsProvider->toolWidth();

	if (toolType == ToolTypes::MarkerPen) {
		width *= 3;
	}

	properties->setWidth(width);
}

void AnnotationPropertiesFactory::setFill(const PropertiesPtr &properties, ToolTypes toolType) const
{
	if (toolType == ToolTypes::MarkerPen) {
		properties->setFillType(FillTypes::BorderAndNoFill);
	} else if (isMarkerTool(toolType)) {
		properties->setFillType(FillTypes::NoBorderAndFill);
	} else if (toolType == ToolTypes::Image) {
		properties->setFillType(FillTypes::BorderAndFill);
	} else if (toolType == ToolTypes::Sticker) {
		properties->setFillType(FillTypes::BorderAndFill);
	} else {
		properties->setFillType(mSettingsProvider->fillType());
	}
}

void AnnotationPropertiesFactory::setShadowEnabled(const PropertiesPtr &properties, ToolTypes toolType) const
{
	if (toolType == ToolTypes::Blur || isMarkerTool(toolType) || toolType == ToolTypes::Image) {
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

bool AnnotationPropertiesFactory::isMarkerTool(ToolTypes toolType) const
{
	return toolType == ToolTypes::MarkerPen || toolType == ToolTypes::MarkerRect || toolType == ToolTypes::MarkerEllipse;
}

void AnnotationPropertiesFactory::setBlurProperties(const PropertiesPtr &properties) const
{
	auto blurProperties = properties.dynamicCast<AnnotationBlurProperties>();
	if (blurProperties != nullptr) {
		blurProperties->setRadius(mSettingsProvider->blurRadius());
	}
}

void AnnotationPropertiesFactory::setStickerProperties(const PropertiesPtr &properties) const
{
	auto stickerProperties = properties.dynamicCast<AnnotationStickerProperties>();
	if (stickerProperties != nullptr) {
		stickerProperties->setPath(mSettingsProvider->sticker());
	}
}

} // namespace kImageAnnotator

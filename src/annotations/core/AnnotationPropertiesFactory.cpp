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

#include "AnnotationPropertiesFactory.h"

namespace kImageAnnotator {

AnnotationPropertiesFactory::AnnotationPropertiesFactory(Config *config, AbstractSettingsProvider *settingsProvider)
{
	mConfig = config;
	mSettingsProvider = settingsProvider;
}

AnnotationProperties *AnnotationPropertiesFactory::create(ToolTypes toolType) const
{
	auto properties = createPropertiesObject(toolType);

	setColor(properties, toolType);
	setTextColor(properties);
	setWidthSize(properties, toolType);
	setFill(properties);
	setShadowEnabled(properties, toolType);
	setPathProperties(properties);
	setTextProperties(properties, toolType);
	setBlurProperties(properties);

	return properties;
}

AnnotationProperties *AnnotationPropertiesFactory::createPropertiesObject(ToolTypes toolType) const
{
	switch (toolType) {
		case ToolTypes::Pen:
		case ToolTypes::MarkerPen:
			return new AnnotationPathProperties();
		case ToolTypes::Number:
		case ToolTypes::Text:
			return new AnnotationTextProperties();
		case ToolTypes::Blur:
			return new AnnotationBlurProperties();
		default:
			return new AnnotationProperties();
	}
}

void AnnotationPropertiesFactory::setColor(AnnotationProperties *properties, ToolTypes toolType) const
{
	auto color = mSettingsProvider->toolColor();

	if (isMarkerTool(toolType)) {
		color.setAlpha(60);
	}

	properties->setColor(color);
}

void AnnotationPropertiesFactory::setTextColor(AnnotationProperties *properties) const
{
	properties->setTextColor(mSettingsProvider->textColor());
}

void AnnotationPropertiesFactory::setWidthSize(AnnotationProperties *properties, ToolTypes toolType) const
{
	auto width = mSettingsProvider->toolWidth();

	if (toolType == ToolTypes::MarkerPen) {
		width *= 3;
	}

	properties->setWidth(width);
}

void AnnotationPropertiesFactory::setFill(AnnotationProperties *properties) const
{
	properties->setFillType(mSettingsProvider->fillType());
}

void AnnotationPropertiesFactory::setShadowEnabled(AnnotationProperties *properties, ToolTypes toolType) const
{
	if (toolType == ToolTypes::Blur || isMarkerTool(toolType) || toolType == ToolTypes::Image) {
		properties->setShadowEnabled(false);
	} else {
		properties->setShadowEnabled(mConfig->itemShadowEnabled());
	}
}

void AnnotationPropertiesFactory::setPathProperties(AnnotationProperties *properties) const
{
	auto pathProperties = dynamic_cast<AnnotationPathProperties *>(properties);
	if (pathProperties != nullptr) {
		pathProperties->setSmoothPathEnabled(mConfig->smoothPathEnabled());
		pathProperties->setSmoothFactor(mConfig->smoothFactor());
	}
}

void AnnotationPropertiesFactory::setTextProperties(AnnotationProperties *properties, ToolTypes toolType) const
{
	auto pathProperties = dynamic_cast<AnnotationTextProperties *>(properties);
	if (pathProperties != nullptr) {
		pathProperties->setFont(mConfig->toolFont(toolType));
	}
}

bool AnnotationPropertiesFactory::isMarkerTool(const ToolTypes &toolType) const
{
	return toolType == ToolTypes::MarkerPen || toolType == ToolTypes::MarkerRect || toolType == ToolTypes::MarkerEllipse;
}

void AnnotationPropertiesFactory::setBlurProperties(AnnotationProperties *properties) const
{
	auto pathProperties = dynamic_cast<AnnotationBlurProperties *>(properties);
	if (pathProperties != nullptr) {
		pathProperties->setRadius(mSettingsProvider->blurRadius());
	}
}

} // namespace kImageAnnotator

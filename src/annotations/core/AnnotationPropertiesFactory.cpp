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

PropertiesPtr AnnotationPropertiesFactory::create(Tools tool) const
{
	return create(tool, false);
}

PropertiesPtr AnnotationPropertiesFactory::createFromConfig(Tools tool) const
{
	return create(tool, true);
}

PropertiesPtr AnnotationPropertiesFactory::create(Tools tool, bool fromConfig) const
{
	auto properties = createPropertiesObject(tool);

	setColor(properties, tool);
	setTextColor(properties);
	setWidthSize(properties);
	setFill(properties, tool);
	setShadowEnabled(properties, tool, fromConfig);
	setPathProperties(properties);
	setTextProperties(properties, tool);
	setObfuscateProperties(properties);
	setStickerProperties(properties);

	return properties;
}

PropertiesPtr AnnotationPropertiesFactory::createPropertiesObject(Tools toolType)
{
	switch (toolType) {
		case Tools::Pen:
		case Tools::MarkerPen:
			return PropertiesPtr(new AnnotationPathProperties());
		case Tools::Number:
		case Tools::NumberPointer:
		case Tools::NumberArrow:
		case Tools::Text:
		case Tools::TextPointer:
		case Tools::TextArrow:
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

	if(toolType == Tools::Duplicate) {
		color.setAlpha(30);
	}

	properties->setColor(color);
}

void AnnotationPropertiesFactory::setTextColor(const PropertiesPtr &properties) const
{
	properties->setTextColor(mSettingsProvider->textColor());
}

void AnnotationPropertiesFactory::setWidthSize(const PropertiesPtr &properties) const
{
	properties->setWidth(mSettingsProvider->toolWidth());
}

void AnnotationPropertiesFactory::setFill(const PropertiesPtr &properties, Tools toolType) const
{
	switch (toolType) {
		case Tools::MarkerPen:
		case Tools::MarkerRect:
		case Tools::MarkerEllipse:
		case Tools::Image:
		case Tools::Sticker:
		case Tools::NumberPointer:
		case Tools::TextPointer:
		case Tools::Duplicate:
			properties->setFillType(mConfig->toolFillType(toolType));
			break;
		default:
			properties->setFillType(mSettingsProvider->fillType());
	}
}

void AnnotationPropertiesFactory::setShadowEnabled(const PropertiesPtr &properties, Tools tool, bool fromConfig) const
{
	auto enabled = fromConfig ? mConfig->shadowEnabled(tool) : mSettingsProvider->shadowEnabled();
	properties->setShadowEnabled(enabled);
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
		textProperties->setFont(mSettingsProvider->font());
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

} // namespace kImageAnnotator

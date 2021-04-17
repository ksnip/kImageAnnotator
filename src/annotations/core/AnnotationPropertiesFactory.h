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

#ifndef KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H
#define KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H

#include "src/annotations/properties/AnnotationProperties.h"
#include "src/annotations/properties/AnnotationPathProperties.h"
#include "src/annotations/properties/AnnotationTextProperties.h"
#include "src/annotations/properties/AnnotationObfuscateProperties.h"
#include "src/annotations/properties/AnnotationStickerProperties.h"
#include "src/backend/Config.h"
#include "src/common/enum/Tools.h"
#include "AbstractSettingsProvider.h"

namespace kImageAnnotator {

class AnnotationPropertiesFactory
{
public:
	explicit AnnotationPropertiesFactory(Config *config, AbstractSettingsProvider *settingsProvider);
	~AnnotationPropertiesFactory() = default;

	PropertiesPtr create(Tools tool) const;
	PropertiesPtr createFromConfig(Tools tool) const;

private:
	Config *mConfig;
	AbstractSettingsProvider *mSettingsProvider;

	PropertiesPtr create(Tools tool, bool fromConfig) const;
	static PropertiesPtr createPropertiesObject(Tools toolType);
	void setShadowEnabled(const PropertiesPtr &properties, Tools tool, bool fromConfig) const;
	void setColor(const PropertiesPtr &properties, Tools toolType) const;
	void setTextColor(const PropertiesPtr &properties) const;
	void setWidthSize(const PropertiesPtr &properties) const;
	void setFill(const PropertiesPtr &properties, Tools toolType) const;
	void setPathProperties(const PropertiesPtr &properties) const;
	void setTextProperties(const PropertiesPtr &properties, Tools toolType) const;
	void setObfuscateProperties(const PropertiesPtr &properties) const;
	void setStickerProperties(const PropertiesPtr &properties) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H

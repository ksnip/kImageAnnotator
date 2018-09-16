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

#ifndef KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H
#define KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H

#include "src/annotations/properties/AnnotationProperties.h"
#include "src/annotations/properties/AnnotationPathProperties.h"
#include "src/backend/Config.h"
#include "src/common/enum/ToolTypes.h"

namespace kImageAnnotator {

class AnnotationPropertiesFactory
{
public:
	explicit AnnotationPropertiesFactory();
	~AnnotationPropertiesFactory() = default;

	AnnotationProperties *createProperties(ToolTypes toolType) const;

private:
	Config *mConfig;
	AnnotationProperties *createPropertiesObject(ToolTypes toolType) const;
	void setShadowEnabled(AnnotationProperties *properties) const;
	void setColor(AnnotationProperties *properties, ToolTypes toolType) const;
	void setTextColor(AnnotationProperties *properties, ToolTypes toolType) const;
	void setSize(AnnotationProperties *properties, ToolTypes toolType) const;
	void setFill(AnnotationProperties *properties, ToolTypes toolType) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONPROPERTIESFACTORY_H

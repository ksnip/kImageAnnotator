/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONOBFUSCATEPROPERTIES_H
#define KIMAGEANNOTATOR_ANNOTATIONOBFUSCATEPROPERTIES_H

#include "AnnotationProperties.h"

namespace kImageAnnotator {

class AnnotationObfuscateProperties;
typedef QSharedPointer<AnnotationObfuscateProperties> ObfuscatePropertiesPtr;

class AnnotationObfuscateProperties : public AnnotationProperties
{
public:
	AnnotationObfuscateProperties() = default;
	AnnotationObfuscateProperties(const AnnotationObfuscateProperties &other);
	~AnnotationObfuscateProperties() override = default;
	PropertiesPtr clone() const override;
	int factor() const;
	void setFactor(int factor);

private:
	int mFactor;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONOBFUSCATEPROPERTIES_H

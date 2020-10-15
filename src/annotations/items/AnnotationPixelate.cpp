/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationPixelate.h"

namespace kImageAnnotator {

AnnotationPixelate::AnnotationPixelate(const QPointF &startPosition, const ObfuscatePropertiesPtr &properties) :
	AbstractAnnotationObfuscate(startPosition, properties)
{

}

AnnotationPixelate::AnnotationPixelate(const AnnotationPixelate &other) : AbstractAnnotationObfuscate(other)
{

}

Tools AnnotationPixelate::toolType() const
{
	return Tools::Pixelate;
}

QImage AnnotationPixelate::obfuscateBackground(const QImage &sceneBehindItem) const
{
	auto width = sceneBehindItem.width();
	auto factor = obfuscateProperties()->factor();
	auto intensity = abs(factor - 21) * 0.01;
	auto scaledWidth = width * intensity;

	if(scaledWidth < 1) {
		return sceneBehindItem;
	}

	auto result   = sceneBehindItem.convertToFormat( QImage::Format_ARGB32_Premultiplied );
	result = result.scaledToWidth(scaledWidth, Qt::FastTransformation );
	result = result.scaledToWidth(width, Qt::FastTransformation );

	return result;
}

} // namespace kImageAnnotator

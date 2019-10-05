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

#include "AnnotationTextProperties.h"

namespace kImageAnnotator {

AnnotationTextProperties::AnnotationTextProperties(const QColor &color, int size) : AnnotationProperties(color, size)
{

}

AnnotationTextProperties::AnnotationTextProperties(const AnnotationTextProperties &other) : AnnotationProperties(other)
{
	mFont = other.mFont;
}

PropertiesPtr AnnotationTextProperties::clone() const
{
	return PropertiesPtr(new AnnotationTextProperties(*this));
}

QFont AnnotationTextProperties::font() const
{
	return mFont;
}

void AnnotationTextProperties::setFont(const QFont &font)
{
	mFont = font;
}

}
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

#include "AnnotationProperties.h"

namespace kImageAnnotator {

AnnotationProperties::AnnotationProperties(const QColor &color, int size)
{
	mColor = color;
	mTextColor = color;
	mWidth = size;
}

AnnotationProperties::AnnotationProperties(const PropertiesPtr &other)
{
	mColor = other->mColor;
	mTextColor = other->mTextColor;
	mWidth = other->mWidth;
	mFillType = other->mFillType;
	mShadowEnabled = other->mShadowEnabled;
}

QColor AnnotationProperties::color() const
{
	return mColor;
}

void AnnotationProperties::setColor(const QColor &color)
{
	mColor = qMove(color);
}

QColor AnnotationProperties::textColor() const
{
	return mTextColor;
}

void AnnotationProperties::setTextColor(const QColor &color)
{
	mTextColor = qMove(color);
}

int AnnotationProperties::width() const
{
	return mWidth;
}

void AnnotationProperties::setWidth(int size)
{
	mWidth = size;
}

FillTypes AnnotationProperties::fillType() const
{
	return mFillType;
}

void AnnotationProperties::setFillType(FillTypes fillType)
{
	mFillType = fillType;
}

bool AnnotationProperties::shadowEnabled() const
{
	return mShadowEnabled;
}

void AnnotationProperties::setShadowEnabled(bool enabled)
{
	mShadowEnabled = enabled;
}

PropertiesPtr AnnotationProperties::clone() const
{
	return PropertiesPtr(new AnnotationProperties(*this));
}

} // namespace kImageAnnotator

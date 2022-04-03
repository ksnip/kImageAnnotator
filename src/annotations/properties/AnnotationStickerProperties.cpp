/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "AnnotationStickerProperties.h"

namespace kImageAnnotator {

AnnotationStickerProperties::AnnotationStickerProperties(const kImageAnnotator::AnnotationStickerProperties &other) :
	AnnotationProperties(other)
{
	this->mPath = other.mPath;
	this->mScaling = other.mScaling;
}

PropertiesPtr kImageAnnotator::AnnotationStickerProperties::clone() const
{
	return PropertiesPtr(new AnnotationStickerProperties(*this));
}

QString AnnotationStickerProperties::path() const
{
	return mPath;
}

void AnnotationStickerProperties::setPath(const QString &path)
{
	mPath = path;
}

qreal AnnotationStickerProperties::scaling() const
{
	return mScaling;
}

void AnnotationStickerProperties::setScaling(qreal scaling)
{
	mScaling = scaling;
}

} // namespace kImageAnnotator

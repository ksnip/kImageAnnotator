/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_IMAGEEFFECTS_H
#define KIMAGEANNOTATOR_IMAGEEFFECTS_H

#include <QMetaType>

namespace kImageAnnotator {

enum class ImageEffects
{
	NoEffect,
	DropShadow,
	Grayscale,
	Border,
	InvertColor,
};

} // namespace kImageAnnotator

Q_DECLARE_METATYPE(kImageAnnotator::ImageEffects);

#endif // KIMAGEANNOTATOR_IMAGEEFFECTS_H

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

#include "NumberRectHelper.h"

namespace kImageAnnotator {

void NumberRectHelper::updateRect(QRectF *rect, const QString &text, const QFont &font) const
{
	auto center = rect->center();
	auto size = getTextRectSize(text, font);
	rect->setSize(size);
	rect->moveCenter(center);
}

QSizeF NumberRectHelper::getTextRectSize(const QString &text, const QFont &font) const
{
	QFontMetricsF metrics(font);
	auto boundingRect = metrics.boundingRect(text).adjusted(-5, -5, 5, 5);
	auto largestSite = boundingRect.width() > boundingRect.height() ? boundingRect.width() : boundingRect.height();
	return { largestSite, largestSite };
}

} // namespace kImageAnnotator

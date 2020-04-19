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

#include "CropSelectionRestrictor.h"

namespace kImageAnnotator {

QRectF &CropSelectionRestrictor::restrictResize(QRectF &newRect, const QRectF &currentRect, const QRectF &maxRect) const
{
	if (newRect.x() < maxRect.x()) {
		newRect.setX(maxRect.x());
	}

	if (newRect.y() < maxRect.y()) {
		newRect.setY(maxRect.y());
	}

	if (newRect.width() < 0) {
		newRect.setWidth(0);
		newRect.moveLeft(currentRect.left());
	}

	if (newRect.height() < 0) {
		newRect.setHeight(0);
		newRect.moveTop(currentRect.top());
	}

	if (newRect.x() + newRect.width() > maxRect.width()) {
		newRect.setWidth(maxRect.width() - newRect.x());
	}

	if (newRect.y() + newRect.height() > maxRect.height()) {
		newRect.setHeight(maxRect.height() - newRect.y());
	}

	return newRect;
}

QRectF &CropSelectionRestrictor::restrictMove(QRectF &newRect, const QRectF &maxRect) const
{
	if (newRect.x() < maxRect.x()) {
		newRect.moveLeft(maxRect.x());
	}

	if (newRect.y() < maxRect.y()) {
		newRect.moveTop(maxRect.y());
	}

	if ((newRect.x() + newRect.width()) > maxRect.width()) {
		newRect.moveTo(maxRect.width() - newRect.width(), newRect.y());
	}

	if ((newRect.y() + newRect.height()) > maxRect.height()) {
		newRect.moveTo(newRect.x(), maxRect.height() - newRect.height());
	}

	return newRect;
}

} // namespave kImageAnnotator
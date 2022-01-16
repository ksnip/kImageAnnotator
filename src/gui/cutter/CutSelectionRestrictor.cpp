/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "CutSelectionRestrictor.h"

namespace kImageAnnotator {

QRectF &CutSelectionRestrictor::restrictResize(QRectF &newRect, const QRectF &currentRect, const QRectF &rectLimit) const
{
	if (newRect.x() < rectLimit.x()) {
		newRect.setX(rectLimit.x());
	}

	if (newRect.y() < rectLimit.y()) {
		newRect.setY(rectLimit.y());
	}

	if (newRect.width() < 0) {
		newRect.setWidth(0);
		newRect.moveLeft(currentRect.left());
	}

	if (newRect.height() < 0) {
		newRect.setHeight(0);
		newRect.moveTop(currentRect.top());
	}

	if (newRect.x() + newRect.width() > rectLimit.width()) {
		newRect.setWidth(rectLimit.width() - newRect.x());
	}

	if (newRect.y() + newRect.height() > rectLimit.height()) {
		newRect.setHeight(rectLimit.height() - newRect.y());
	}

	return newRect;
}

QRectF &CutSelectionRestrictor::restrictMove(QRectF &newRect, const QRectF &rectLimit) const
{
	if (newRect.x() < rectLimit.x()) {
		newRect.moveLeft(rectLimit.x());
	}

	if (newRect.y() < rectLimit.y()) {
		newRect.moveTop(rectLimit.y());
	}

	if ((newRect.x() + newRect.width()) > rectLimit.width()) {
		newRect.moveTo(rectLimit.width() - newRect.width(), newRect.y());
	}

	if ((newRect.y() + newRect.height()) > rectLimit.height()) {
		newRect.moveTo(newRect.x(), rectLimit.height() - newRect.height());
	}

	return newRect;
}
} // kImageAnnotator namespace

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

#ifndef KIMAGEANNOTATOR_CROPSELECTIONMOVEHELPER_H
#define KIMAGEANNOTATOR_CROPSELECTIONMOVEHELPER_H

#include <QPointF>
#include <QRectF>

namespace kImageAnnotator {

class CropSelectionMoveHelper
{
public:
	explicit CropSelectionMoveHelper();
	~CropSelectionMoveHelper() = default;
	void grabSelection(const QPointF &position, const QRectF &selection);
	void releaseSelection();
	bool isSelectionGabbed() const;
	QPointF grabOffset() const;

private:
	bool mIsSelectionGabbed{};
	QPointF mGrabOffset;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPSELECTIONMOVEHELPER_H

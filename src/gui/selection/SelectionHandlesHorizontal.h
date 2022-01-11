/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_SELECTIONHANDLESHORIZONTAL_H
#define KIMAGEANNOTATOR_SELECTIONHANDLESHORIZONTAL_H

#include <QRectF>
#include <QVector>

#include "ISelectionHandles.h"
#include "src/common/provider/ScaledSizeProvider.h"
#include "src/common/helper/ShapeHelper.h"

namespace kImageAnnotator {

class SelectionHandlesHorizontal : public ISelectionHandles
{
public:
	explicit SelectionHandlesHorizontal();
	~SelectionHandlesHorizontal() override = default;
	QVector<QRectF> handles() const override;
	void grabHandle(const QPointF &position, const QRectF &selection) override;
	void releaseHandle() override;
	int grabbedIndex() const override;
	void updateHandles(const QRectF &selection) override;
	bool isHandleGrabbed() const override;
	QPointF grabOffset() const override;
	void applyZoomValue(double value) override;

private:
	QMap<int, QRectF> mHandles;
	int mGrabbedIndex;
	QPointF mGrabOffset;
	double mHandleSize;
};

} // namespace kImageAnnotator


#endif //KIMAGEANNOTATOR_SELECTIONHANDLESHORIZONTAL_H

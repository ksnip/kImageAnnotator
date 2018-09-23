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

#ifndef KIMAGEANNOTATOR_CROPHANDLES_H
#define KIMAGEANNOTATOR_CROPHANDLES_H

#include <QRectF>
#include <QList>

#include "CropSelectionRestrictor.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/common/helper/ShapeHelper.h"
#include "src/common/constants/Constants.h"

namespace kImageAnnotator {

class CropSelectionHandler : public QObject
{
Q_OBJECT
public:
	explicit CropSelectionHandler(AnnotationArea *annotationArea);
	~CropSelectionHandler() override = default;
	QRectF selection() const;
	QVector<QRectF> selectionHandles() const;
	void grab(const QPointF &position);
	void move(const QPointF &position);
	void release();
	void setWidth(int width);
	void setHeight(int height);
	void setPositionX(int x);
	void setPositionY(int y);
	void resetSelection();
	bool isInMotion() const;

signals:
	void selectionChanged(const QRectF &rect) const;

private:
	AnnotationArea *mAnnotationArea;
	QRectF mSelection;
	QRectF mMaxSelection;
	QVector<QRectF> mSelectionHandles;
	bool mIsInMotion;
	int mGrabbedHandleIndex;
	QPointF mGrabOffset;
	CropSelectionRestrictor mSelectionRestrictor;

	void update();
	void notifyAboutChanged() const;
	void updateHandles();
	void setSelection(const QRectF &rect);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPHANDLES_H

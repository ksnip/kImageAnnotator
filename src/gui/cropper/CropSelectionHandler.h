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

#ifndef KIMAGEANNOTATOR_CROPHANDLES_H
#define KIMAGEANNOTATOR_CROPHANDLES_H

#include <QRectF>
#include <QList>

#include "CropSelectionRestrictor.h"
#include "CropHandles.h"
#include "CropSelectionMoveHelper.h"
#include "src/annotations/core/AnnotationArea.h"

namespace kImageAnnotator {

class CropSelectionHandler : public QObject
{
Q_OBJECT
public:
	explicit CropSelectionHandler();
	~CropSelectionHandler() override = default;
	void init(AnnotationArea *annotationArea);
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
	bool selectionContains(const QPointF &pos) const;

signals:
	void selectionChanged(const QRectF &rect) const;

private:
	AnnotationArea *mAnnotationArea;
	QRectF mSelection;
	QRectF mMaxSelection;
	CropSelectionRestrictor mSelectionRestrictor;
	CropHandles mCropHandles;
	CropSelectionMoveHelper mMoveHelper;

	void update();
	void notifyAboutChange() const;
	void setSelection(const QRectF &rect);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPHANDLES_H

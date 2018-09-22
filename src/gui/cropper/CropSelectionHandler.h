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

#include <QRect>
#include <QList>

#include "src/annotations/core/AnnotationArea.h"
#include "src/common/helper/ShapeHelper.h"

namespace kImageAnnotator {

class CropSelectionHandler : public QObject
{
Q_OBJECT
public:
	explicit CropSelectionHandler(AnnotationArea *annotationArea);
	~CropSelectionHandler() override = default;
	QRect selection() const;
	QList<QRect> selectionHandles() const;
	void grabHandle(const QPoint &position);
	void moveHandle(const QPoint &position);
	void setWidth(int width);
	void setHeight(int height);
	void setPositionX(int x);
	void setPositionY(int y);
	void resetSelection();

signals:
	void selectionChanged(const QRect &rect) const;

private:
	AnnotationArea *mAnnotationArea;
	QRect mSelection;
	QSize mMaxSelectionSize;
	QList<QRect> mSelectionHandles;

	void notifyAboutChanged() const;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPHANDLES_H

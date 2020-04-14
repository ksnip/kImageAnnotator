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

#ifndef KIMAGEANNOTATOR_CROPVIEW_H
#define KIMAGEANNOTATOR_CROPVIEW_H

#include <QGraphicsView>

#include "CropSelectionHandler.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/common/helper/KeyHelper.h"

namespace kImageAnnotator {

class CropView : public QGraphicsView
{
Q_OBJECT
public:
	explicit CropView(CropSelectionHandler *cropSelectionHandler, KeyHelper *keyHelper);
	~CropView() override = default;
	void init(AnnotationArea *annotationArea);

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void drawForeground(QPainter *painter, const QRectF &rect) override;

private:
	CropSelectionHandler *mCropSelectionHandler;
	KeyHelper *mKeyHelper;

	void updateCursor(const QPointF &pos);
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPVIEW_H

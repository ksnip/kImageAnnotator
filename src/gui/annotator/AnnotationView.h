/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KIMAGEANNOTATOR_ANNOTATIONVIEW_H
#define KIMAGEANNOTATOR_ANNOTATIONVIEW_H

#include <QMouseEvent>
#include <QScrollBar>
#include <QGuiApplication>

#include "src/gui/scrollAndZoomView/ScrollAndZoomView.h"
#include "src/common/helper/KeyHelper.h"
#include "src/annotations/core/AnnotationArea.h"
#include "src/annotations/misc/CanvasPainter.h"
#include "src/gui/scrollAndZoomView/ViewZoomer.h"

namespace kImageAnnotator {

class AnnotationView : public ScrollAndZoomView
{
	Q_OBJECT
public:
	explicit AnnotationView(QWidget *parent);
	~AnnotationView() override = default;

protected:
	void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	CanvasPainter mCanvasPainter;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ANNOTATIONVIEW_H

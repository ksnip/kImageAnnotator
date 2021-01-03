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

#include "CropView.h"

namespace kImageAnnotator {

CropView::CropView(SelectionHandler *cropSelectionHandler, KeyHelper *keyHelper) :
	BaseSelectionView(cropSelectionHandler, keyHelper)
{
}

void CropView::drawForeground(QPainter *painter, const QRectF &rect)
{
	painter->setClipRegion(QRegion(sceneRect().toRect()).subtracted(QRegion(currentSelection().toRect())));
	painter->setBrush(QColor(0, 0, 0, 150));
	painter->drawRect(sceneRect());

	BaseSelectionView::drawForeground(painter, rect);
}

void CropView::drawBackground(QPainter *painter, const QRectF &rect)
{
	auto annotationArea = dynamic_cast<AnnotationArea *>(scene());
	mCanvasPainter.paint(painter, annotationArea->canvasRect(), annotationArea->canvasColor());
}

} // namespace kImageAnnotator

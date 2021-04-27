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

#ifndef KIMAGEANNOTATOR_CROPVIEW_H
#define KIMAGEANNOTATOR_CROPVIEW_H

#include "src/gui/selection/BaseSelectionView.h"
#include "src/annotations/misc/CanvasPainter.h"

namespace kImageAnnotator {

class CropView : public BaseSelectionView
{
Q_OBJECT
public:
	explicit CropView(SelectionHandler *selectionHandler, KeyHelper *keyHelper, QWidget *parent);
	~CropView() override = default;

protected:
	void drawForeground(QPainter *painter, const QRectF &rect) override;
	void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
	CanvasPainter mCanvasPainter;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_CROPVIEW_H

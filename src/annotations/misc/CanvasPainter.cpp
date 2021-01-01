/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "CanvasPainter.h"

namespace kImageAnnotator {

CanvasPainter::CanvasPainter() :
	mCanvasBackground(new QImage(QSize(20, 20), QImage::Format_ARGB32_Premultiplied))
{
	createTiledBackground();
}

CanvasPainter::~CanvasPainter()
{
	delete mCanvasBackground;
}

void CanvasPainter::paint(QPainter *painter, const QRectF &rect, const QColor &color)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(*mCanvasBackground);
	painter->drawRect(rect);
	painter->setBrush(color);
	painter->drawRect(rect);
}

void CanvasPainter::createTiledBackground()
{
	mCanvasBackground->fill(Qt::white);
	QPainter painter(mCanvasBackground);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::gray);
	painter.drawRect(0, 0, 10, 10);
	painter.drawRect(10, 10, 20, 20);
}

} // namespace kImageAnnotator
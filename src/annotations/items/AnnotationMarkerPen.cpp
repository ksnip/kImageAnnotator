/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationMarkerPen.h"

namespace kImageAnnotator {

AnnotationMarkerPen::AnnotationMarkerPen(const QPointF &startPosition, const PropertiesPtr &properties) :
	AnnotationPen(startPosition, properties)
{

}

Tools AnnotationMarkerPen::toolType() const
{
	return Tools::MarkerPen;
}

void AnnotationMarkerPen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setCompositionMode(QPainter::CompositionMode_Multiply);
	AnnotationPen::paint(painter, option, widget);
}
} // namespace kImageAnnotator